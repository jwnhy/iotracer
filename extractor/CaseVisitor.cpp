#include "clang/AST/AST.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

#include <iostream>

using namespace llvm;
using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;

template <typename... Args>
std::string str_format(const std::string &format, Args... args) {
  int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
  if (size_s <= 0) {
    throw std::runtime_error("Error during formatting.");
  }
  auto size = static_cast<size_t>(size_s);
  std::unique_ptr<char[]> buf(new char[size]);
  std::snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(), buf.get() + size - 1);
}

struct Typ {
  std::string name;
  std::string format_str;

  bool is_pointer;
  uint64_t size;

  bool is_primitive;
  bool is_array;
  bool is_struct;
  bool is_union;
  // for array/pointer
  std::shared_ptr<Typ> sub_type;
  // for array
  uint64_t nr;
};

struct Field {
  std::string name;
  uint64_t offset;
  std::shared_ptr<Typ> type;
};

struct Record {
  std::string name;
  std::vector<std::shared_ptr<Field>> fields;
};

std::unordered_map<std::string, std::shared_ptr<Record>> record_map;
std::vector<std::tuple<uint64_t, std::string>> ioctl_map;

const clang::RecordDecl *getUnderlyingRecordType(clang::QualType qt,
                                                 ASTContext &ctx) {
  using namespace clang;

  while (true) {
    qt = qt.getDesugaredType(ctx);

    if (const clang::PointerType *ptrType = qt->getAs<clang::PointerType>()) {
      qt = ptrType->getPointeeType();
      continue;
    }
    if (const TypedefType *typedefType = dyn_cast<TypedefType>(qt)) {
      qt = typedefType->desugar();
      continue;
    }
    if (const RecordType *recordType = qt->getAs<RecordType>()) {
      return recordType->getDecl();
    }

    break;
  }
  return nullptr;
}

void generate_field_printer() {

}

struct Record convertRecordDecl(const clang::RecordDecl *recordDecl);

struct Typ convertTyp(const clang::QualType &qt, ASTContext &ctx) {
  struct Typ typ;
  auto uqt = qt.getCanonicalType().getUnqualifiedType();
  typ.name = uqt.getAsString();
  typ.size = ctx.getTypeSize(qt);
  if (uqt->isBuiltinType()) {
    // kernel does not have float, everything else is just int
    typ.format_str = "0x%lx";
    typ.is_primitive = true;
  } else if (uqt->isPointerType()) {
    auto pointeeType =
        uqt->getPointeeType().getCanonicalType().getUnqualifiedType();
    typ.sub_type = std::make_unique<Typ>(convertTyp(pointeeType, ctx));
    typ.format_str = "0x%lx";
    typ.is_pointer = true;
  } else if (uqt->isConstantArrayType()) {
    auto subType = uqt->getArrayElementTypeNoTypeQual();
    if (subType->isCharType()) {
      typ.format_str = "%s";
    } else {
      typ.format_str = "0x%lx";
    }
    typ.sub_type = std::make_unique<Typ>(convertTyp(QualType(subType, 0), ctx));
    typ.nr = dyn_cast<clang::ConstantArrayType>(uqt.getTypePtr())
                 ->getSize()
                 .getZExtValue();
    typ.is_array = true;
  } else if (uqt->isStructureType()) {
    auto recordDecl = uqt->getAsStructureType()->getDecl();
    struct Record record = convertRecordDecl(recordDecl);
    record_map[typ.name] = std::make_shared<Record>(record);
    typ.is_struct = true;
  } else if (uqt->isUnionType()) {
    auto recordDecl = uqt->getAsUnionType()->getDecl();
    struct Record record = convertRecordDecl(recordDecl);
    record_map[typ.name] = std::make_shared<Record>(record);
    typ.is_union = true;
  }

  return typ;
}

struct Field convertFieldDecl(const clang::FieldDecl *fieldDecl) {
  struct Field field;
  field.name = fieldDecl->getName();
  field.offset = fieldDecl->getASTContext().getFieldOffset(fieldDecl);
  QualType fieldType =
      fieldDecl->getType().getCanonicalType().getUnqualifiedType();
  field.type =
      std::make_shared<Typ>(convertTyp(fieldType, fieldDecl->getASTContext()));
  return field;
}

struct Record convertRecordDecl(const clang::RecordDecl *recordDecl) {
  struct Record record;
  record.name = QualType(recordDecl->getTypeForDecl(), 0).getAsString();
  auto &ctx = recordDecl->getASTContext();

  for (const auto *field : recordDecl->fields()) {
    record.fields.push_back(std::make_shared<Field>(convertFieldDecl(field)));
  }

  return record;
}

class CaseVisitor : public MatchFinder::MatchCallback {
public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const IntegerLiteral *IL =
            Result.Nodes.getNodeAs<IntegerLiteral>("case_value")) {
      this->cmd = IL->getValue().getZExtValue();
    }
    if (const auto *P = Result.Nodes.getNodeAs<ParmVarDecl>("param")) {
      auto *record = getUnderlyingRecordType(P->getType(), P->getASTContext());
      if (record) {
        auto recordDecl = record->getDefinition();
        if (recordDecl) {
          struct Record rec = convertRecordDecl(recordDecl);
          ioctl_map.push_back(std::make_tuple(this->cmd, rec.name));
          record_map[rec.name] = std::make_shared<Record>(rec);
        }
      }
    }
  }

private:
  uint64_t cmd;
};

static cl::OptionCategory MyToolCategory("case-visitor options");
static cl::opt<std::string>
    IoctlFuncArg("func", cl::desc("Specify the function name to search for"),
                 cl::value_desc("function name"), cl::cat(MyToolCategory));
static cl::opt<std::string> HandlerFuncArg(
    "case",
    cl::desc("Specify the substring in ioctl case handler name to search for"),
    cl::value_desc("handler function substring"), cl::cat(MyToolCategory));

static cl::opt<std::string> HandlerParamArg(
    "param",
    cl::desc("Specify the parameter name to search for in ioctl case handler"),
    cl::value_desc("handler function parameter"), cl::cat(MyToolCategory));

static cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

int main(int argc, const char **argv) {
  auto OptionsParser = CommonOptionsParser::create(argc, argv, MyToolCategory);
  if (!OptionsParser || IoctlFuncArg.empty()) {
    cl::PrintHelpMessage();
    return 0;
  }
  ClangTool Tool(OptionsParser->getCompilations(),
                 OptionsParser->getSourcePathList());

  CaseVisitor Visitor;
  MatchFinder Finder;

  char *sstr = (char *)".*%s.*";
  char handler_buf[30];
  sprintf(handler_buf, sstr, HandlerFuncArg.c_str());

  char *param_sstr = (char *)".*%s.*";
  char param_buf[30];
  sprintf(param_buf, sstr, HandlerParamArg.c_str());

  DeclarationMatcher CaseMatcher = functionDecl(
      decl().bind("ioctl_handler"), isDefinition(), hasName(IoctlFuncArg),
      hasDescendant(switchStmt(forEachDescendant(
          caseStmt(has(ignoringParenCasts(expr().bind("case_value"))),
                   forEachDescendant(callExpr(callee(
                       functionDecl(
                           matchesName(handler_buf),
                           hasAnyParameter(parmVarDecl(matchesName(param_buf))
                                               .bind("param")))
                           .bind("case_handler")))))
              .bind("case")))));
  Finder.addMatcher(CaseMatcher, &Visitor);

  Tool.run(newFrontendActionFactory(&Finder).get());
  for (auto [cmd, name] : ioctl_map) {
    std::cout << "ioctl cmd: " << std::hex << cmd << ", type: " << name
              << std::endl;
  }
  for (auto [name, record] : record_map) {
    std::cout << "record name: " << name << std::endl;
    for (auto field : record->fields) {
      std::cout << "  field name: " << field->name
                << ", type: " << field->type->name
                << ", offset: " << field->offset
                << ", size: " << field->type->size
                << ", format: " << field->type->format_str << std::endl;
    }
  }
}
