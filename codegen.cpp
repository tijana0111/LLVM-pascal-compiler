#include "codegen.hpp"

/* kontekst */
LLVMContext theContext;
/* mapa koja preslikava lokalne int promenljive u njihove alokatore */
map<string, AllocaInst*> namedValues;
/* mapa koja preslikava lokalne bool promenljive u njihove alokatore */
map<string, AllocaInst*> boolNamedValues;
/* tablica koja sadrzi 0 za bool promenljive, 1 za int*/
map<string, char> tablica;
/* builder za pravljenje instrukcija */
IRBuilder<> builder(theContext);
/* optimizacija funkcija */
Module* TheModule;
llvm::legacy::FunctionPassManager* TheFPM;


/* main f-ja */
Function* m = nullptr;

/* eksterna f-ja print_int */
Function* printd = nullptr;
/* eksterna f-ja print_l */
Function* printdl = nullptr;

/* kreiranje alokatora int promenljive */
AllocaInst* createEntryBlockAlloca(Function* theFunction, const string& name) {
  IRBuilder<> b(&theFunction->getEntryBlock(), theFunction->getEntryBlock().begin());
  return b.CreateAlloca(Type::getInt32Ty(theContext), 0, name.c_str());
}

/* kreiranje alokatora bool promenljive */
AllocaInst* createBEntryBlockAlloca(Function* theFunction, const string& name) {
  IRBuilder<> b(&theFunction->getEntryBlock(), theFunction->getEntryBlock().begin());
  return b.CreateAlloca(Type::getInt1Ty(theContext), 0, name.c_str());
}

void initializeModuleAndPassManager() {
  TheModule = new llvm::Module("Moj Modul", theContext);
  TheFPM = new llvm::legacy::FunctionPassManager(TheModule);

  TheFPM->add(createInstructionCombiningPass());
  TheFPM->add(createReassociatePass());
  TheFPM->add(createGVNPass());
  TheFPM->add(createCFGSimplificationPass());
  TheFPM->doInitialization();
  
  string name("print_int");
  vector<Type*> v(1, Type::getInt32Ty(theContext));
  /* fja vraca int */
  FunctionType* fp = FunctionType::get(Type::getInt32Ty(theContext), v, false);
  printd = Function::Create(fp, Function::ExternalLinkage, name, TheModule);
  
  /*ptint za logicke izraze*/
  string namel("print_l");
  vector<Type*> vl(1, Type::getInt1Ty(theContext));
  /* fja vraca int */
  FunctionType* fpl = FunctionType::get(Type::getInt32Ty(theContext), vl, false);
  printdl = Function::Create(fpl, Function::ExternalLinkage, namel, TheModule);
 
}




