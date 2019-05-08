#ifndef __CODEGEN_HPP__
#define __CODEGEN_HPP__ 1

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/TargetSelect.h"

using namespace std;
using namespace llvm;

/* trenutni modul */
extern Module* TheModule;
/* kontekst */
extern LLVMContext theContext;
/* mapa koja preslikava lokalne int promenljive u njihove alokatore */
extern map<string, AllocaInst*> namedValues;
/* mapa koja preslikava lokalne bool promenljive u njihove alokatore */
extern map<string, AllocaInst*> boolNamedValues;

extern map<string, char> tablica;
/* builder za pravljenje instrukcija */
extern IRBuilder<> builder;
/* optimizacija funkcija */
extern llvm::legacy::FunctionPassManager* TheFPM;

/* inicijalizacija modula i pass-manager-a */
void initializeModuleAndPassManager();

/* kreiranje alokatora int promenljive */
AllocaInst* createEntryBlockAlloca(Function* TheFunction, const string& name);

/* kreiranje alokatora bool promenljive */
AllocaInst* createBEntryBlockAlloca(Function* TheFunction, const string& name);


extern Function* m;
extern Function* printd;
extern Function* printdl;
#endif

