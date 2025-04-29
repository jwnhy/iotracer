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

  bool is_pointer = 0;
  uint64_t size;

  bool is_primitive = 0;
  bool is_array = 0;
  bool is_struct = 0;
  bool is_union = 0;
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

void generateTypeDefinition(const std::shared_ptr<Typ> &typ, std::ostream &os) {
  if (typ->is_primitive && !typ->is_array) {
    os << typ->name;
  } else if (typ->is_pointer) {
    os << typ->name << "*";
  } else if (typ->is_array) {
    os << typ->sub_type->name;
  } else if (typ->is_struct || typ->is_union) {
    os << typ->name; // 结构体或联合类型
  }
}

void generateStructDefinition(const std::shared_ptr<Record> &record,
                              std::ostream &os) {
  auto name = record->name;
  auto hasStruct = name.find("struct") != std::string::npos;
  if (hasStruct) {
    os << name << " {\n";
  } else {
    os << "typedef struct" << " {\n";
  }

  for (const auto &field : record->fields) {
    generateTypeDefinition(field->type, os);
    os << "    " << field->name << " ";
    if (field->type->is_array) {
      os << "[" << field->type->nr << "]";
    }
    os << ";\n";
  }

  if (hasStruct) {
    os << "};\n";
  } else {
    os << "}" << name << ";\n";
  }
}

void generateSizeofarg(
    const std::unordered_map<std::string, std::shared_ptr<Record>> &record_map,
    const std::vector<std::tuple<uint64_t, std::string>> &ioctl_map,
    std::ostream &out) {
  out << "static inline uint64_t sizeofarg(int cmd) {\n";
  out << "    switch (cmd) {\n";
  for (const auto &[cmd, record_name] : ioctl_map) {
    out << "    case " << cmd << ": return sizeof(" << record_name << ");\n";
  }
  out << "    default: return 0;\n";
  out << "    }\n";
  out << "}\n\n";
}

void generatePrinterForType(
    const std::shared_ptr<Typ> &type, const std::string &accessor, int indent,
    const std::unordered_map<std::string, std::shared_ptr<Record>> &record_map,
    std::ostream &out) {
  std::string indent_str(indent, ' ');

  if (type->is_primitive) {
    if (type->format_str.empty()) {
      out << indent_str << "printf(\"" << accessor
          << ": %lu\\n\", (unsigned long)(" << accessor << "));\n";
    } else {
      out << indent_str << "printf(\"" << accessor << ": " << type->format_str
          << "\\n\", " << accessor << ");\n";
    }
  } else if (type->is_pointer) {
    out << indent_str << "if (" << accessor << ") {\n";
    generatePrinterForType(type->sub_type, "*" + accessor, indent + 4,
                           record_map, out);
    out << indent_str << "} else {\n";
    out << indent_str << "    printf(\"" << accessor << ": NULL\\n\");\n";
    out << indent_str << "}\n";
  } else if (type->is_array) {
    out << indent_str << "for (uint64_t i = 0; i < " << type->nr
        << "; ++i) {\n";
    generatePrinterForType(type->sub_type, accessor + "[i]", indent + 4,
                           record_map, out);
    out << indent_str << "}\n";
  } else if (type->is_struct) {
    // 查找Record
    auto it = record_map.find(type->name);
    if (it != record_map.end()) {
      auto nospace_name = type->name;
      std::replace(nospace_name.begin(), nospace_name.end(), ' ', '_');
      out << indent_str << "printf(\"" << accessor << ":\\n\");\n";
      out << indent_str << "printer_" << nospace_name << "(&(" << accessor
          << "));\n";
    } else {
      out << indent_str << "printf(\"" << accessor
          << ": <unknown struct>\\n\");\n";
    }
  } else if (type->is_union) {
    out << indent_str << "/* Union printing not supported yet */\n";
  } else {
    out << indent_str << "printf(\"" << accessor << ": <unknown type>\\n\");\n";
  }
}

void generatePrinter(
    const std::unordered_map<std::string, std::shared_ptr<Record>> &record_map,
    std::ostream &out) {
  for (const auto &[record_name, record_ptr] : record_map) {
    auto nospace_name = record_name;
    std::replace(nospace_name.begin(), nospace_name.end(), ' ', '_');
    out << "static inline void printer_" << nospace_name << "(" << record_name
        << "* obj) {\n";
    out << "    printf(\"" << record_name << " {\\n\");\n";
    for (const auto &field : record_ptr->fields) {
      std::string accessor = "obj->" + field->name;
      generatePrinterForType(field->type, accessor, 4, record_map, out);
    }
    out << "    printf(\"}\\n\");\n";
    out << "}\n\n";
  }
}

void generatePrintarg(
    const std::unordered_map<std::string, std::shared_ptr<Record>> &record_map,
    const std::vector<std::tuple<uint64_t, std::string>> &ioctl_map,
    std::ostream &out) {
  out << "static inline void printarg(int cmd, void* arg) {\n";
  out << "    switch (cmd) {\n";
  for (const auto &[cmd, record_name] : ioctl_map) {
    // 确保record存在
    if (record_map.count(record_name)) {
      auto nospace_name = record_name;
      std::replace(nospace_name.begin(), nospace_name.end(), ' ', '_');

      out << "    case " << cmd << ":\n";
      out << "        printer_" << nospace_name << "((" << record_name
          << "*)arg);\n";
      out << "        break;\n";
    }
  }
  out << "    default:\n";
  out << "        printf(\"Unknown cmd: %d\\n\", cmd);\n";
  out << "        break;\n";
  out << "    }\n";
  out << "}\n\n";
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
      typ.is_primitive = true;
      typ.is_array = true;
    } else {
      typ.format_str = "0x%lx";
      typ.is_array = true;
    }
    typ.sub_type = std::make_unique<Typ>(convertTyp(QualType(subType, 0), ctx));
    typ.nr = dyn_cast<clang::ConstantArrayType>(uqt.getTypePtr())
                 ->getSize()
                 .getZExtValue();
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
  virtual void run(const MatchFinder::MatchResult &Result) override {
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

  for (const auto record : record_map) {
    generateStructDefinition(record.second, std::cout);
  }
  generateSizeofarg(record_map, ioctl_map, std::cout);
  generatePrinter(record_map, std::cout);
  generatePrintarg(record_map, ioctl_map, std::cout);
}
