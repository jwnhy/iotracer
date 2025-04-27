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

class CaseVisitor : public MatchFinder::MatchCallback {
public:
  virtual void run(const MatchFinder::MatchResult &Result) {
    if (const Decl *FS = Result.Nodes.getNodeAs<Decl>("func")) {
      FS->dump();
    }
  }
};

static cl::OptionCategory MyToolCategory("case-visitor options");
static cl::opt<std::string>
    IoctlFuncArg("func", cl::desc("Specify the function name to search for"),
                 cl::value_desc("function name"),
                 cl::cat(MyToolCategory)
                 );
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

  DeclarationMatcher CaseMatcher =
      functionDecl(decl().bind("func"), isDefinition(), hasName(IoctlFuncArg));
  Finder.addMatcher(CaseMatcher, &Visitor);

  return Tool.run(newFrontendActionFactory(&Finder).get());
}
