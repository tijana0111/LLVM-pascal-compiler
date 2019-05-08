#include "naredba.hpp"

#include <map>
#include <iostream>

using namespace std;


IspisIzraza::~IspisIzraza() {
  delete _i;
}

IspisIzraza::IspisIzraza(const IspisIzraza &n) {
  _i = n._i->klon();
}

IspisIzraza& IspisIzraza::operator=(const IspisIzraza &n) {
  if (this != &n) {
    delete _i;
    _i = n._i->klon();
  }
  return *this;
}

IspisLIzraza::~IspisLIzraza() {
  delete _i;
}

IspisLIzraza::IspisLIzraza(const IspisLIzraza &n) {
  _i = n._i->klon();
}

IspisLIzraza& IspisLIzraza::operator=(const IspisLIzraza &n) {
  if (this != &n) {
    delete _i;
    _i = n._i->klon();
  }
  return *this;
}

Dodela::~Dodela() {
  delete _i;
}

Dodela::Dodela(const Dodela& n) {
  _i = n._i->klon();
  _l = n._l;
}

Dodela& Dodela::operator=(const Dodela& n) {
  if (this != &n) {
    delete _i;
    _i = n._i->klon();
    _l = n._l;
  }
  return *this;
}


BDodela::~BDodela() {
  delete _i;
}

BDodela::BDodela(const BDodela& n) {
  _i = n._i->klon();
  _l = n._l;
}

BDodela& BDodela::operator=(const BDodela& n) {
  if (this != &n) {
    delete _i;
    _i = n._i->klon();
    _l = n._l;
  }
  return *this;
}

InicijalizacijaSaDodelom::~InicijalizacijaSaDodelom() {
  delete _i;
}

InicijalizacijaSaDodelom::InicijalizacijaSaDodelom(const InicijalizacijaSaDodelom& n) {
  _i = n._i->klon();
  _l = n._l;
}

InicijalizacijaSaDodelom& InicijalizacijaSaDodelom::operator=(const InicijalizacijaSaDodelom& n) {
  if (this != &n) {
    delete _i;
    _i = n._i->klon();
    _l = n._l;
  }
  return *this;
}

BInicijalizacijaSaDodelom::~BInicijalizacijaSaDodelom() {
  delete _i;
}

BInicijalizacijaSaDodelom::BInicijalizacijaSaDodelom(const BInicijalizacijaSaDodelom& n) {
  _i = n._i->klon();
  _l = n._l;
}

BInicijalizacijaSaDodelom& BInicijalizacijaSaDodelom::operator=(const BInicijalizacijaSaDodelom& n) {
  if (this != &n) {
    delete _i;
    _i = n._i->klon();
    _l = n._l;
  }
  return *this;
}

Blok::~Blok() {
  for (auto n : _v)
    delete n;
}


NaredbaIfThen::~NaredbaIfThen() {
  delete _i;
  delete _n1;
}

NaredbaIfThenElse::~NaredbaIfThenElse() {
  delete _i;
  delete _n1;
  delete _n2;
}

NaredbaWhile::~NaredbaWhile() {
  delete _i;
  delete _n1;
}


/******************** codegen *************************/

Value* IspisIzraza::codegen() const {

  /* Jedan argument fje print_int */
  vector<Value*> argV;
  argV.push_back(_i->codegen());
  if (!argV.back())
    return nullptr;

  /* Kreiranje poziva fje */
  builder.CreateCall(printd, argV, "calltmp");
  return ConstantInt::get(theContext, APInt(32, 0));
}
Value* IspisLIzraza::codegen() const {

  /* Jedan argument fje print_l */
  vector<Value*> argV;
  argV.push_back(_i->codegen());
  if (!argV.back())
    return nullptr;

  /* Kreiranje poziva fje */
  builder.CreateCall(printdl, argV, "calltmp");
  return ConstantInt::get(theContext, APInt(32, 0));
}

Value* Dodela::codegen() const {
  Value *r = _i->codegen();
  /* Promenljive moraju da budu deklarisane pre koriscenja */
  if (!namedValues.count(_l)){
	  cerr << "Promenljiva "<< _l <<" nije deklarisana." << endl;
	  exit(EXIT_FAILURE);
  }
  
  AllocaInst* alloca = namedValues[_l];
  /* Cuvanje vrednosti */
  builder.CreateStore(r, alloca);
  return ConstantInt::get(theContext, APInt(32, 0));
}

Value* BDodela::codegen() const {
  Value *r = _i->codegen();
  /* Promenljive moraju da budu deklarisane pre koriscenja */
  if (!boolNamedValues.count(_l)){
	  cerr << "Promenljiva "<< _l <<" nije deklarisana." << endl;
	  exit(EXIT_FAILURE);
  }
  
  AllocaInst* alloca = boolNamedValues[_l];
  /* Cuvanje vrednosti */
  builder.CreateStore(r, alloca);
  return ConstantInt::get(theContext, APInt(32, 0));
}

Value* Inicijalizacija::codegen() const {
  
  Value *r = ConstantInt::get(theContext, APInt(32, 0));
  /* Ako promenljiva nije alocirana */
  if (!namedValues.count(_l) and !boolNamedValues.count(_l))
    namedValues[_l] = createEntryBlockAlloca(m, _l);
  else{
	  cerr << "Promenljiva "<< _l <<" je vec deklarisana." << endl;
	  exit(EXIT_FAILURE);
  }
  AllocaInst* alloca = namedValues[_l];
  /* Cuvanje vrednosti */
  builder.CreateStore(r, alloca);
  
  return ConstantInt::get(theContext, APInt(32, 0));
}

Value* InicijalizacijaSaDodelom::codegen() const {
  Value *r = _i->codegen();
  /* Ako promenljiva nije alocirana, alociramo je */
  if (!namedValues.count(_l) and !boolNamedValues.count(_l))
    namedValues[_l] = createEntryBlockAlloca(m, _l);
  else{
	  cerr << "Promenljiva "<< _l <<" je vec deklarisana." << endl;
	  exit(EXIT_FAILURE);
  }
  AllocaInst* alloca = namedValues[_l];
  /* Cuvanje vrednosti */
  builder.CreateStore(r, alloca);
  
  return ConstantInt::get(theContext, APInt(32, 0));
}


Value* BInicijalizacija::codegen() const {
  Value *r = ConstantInt::get(Type::getInt1Ty(theContext), 1);
  /* Ako promenljiva nije alocirana */
  if (!namedValues.count(_l) and !boolNamedValues.count(_l))
    boolNamedValues[_l] = createBEntryBlockAlloca(m, _l);
  else{
	  cerr << "Promenljiva "<< _l <<" je vec deklarisana." << endl;
	  exit(EXIT_FAILURE);
  }
  AllocaInst* alloca = boolNamedValues[_l];
  /* Cuvanje vrednosti */
  builder.CreateStore(r, alloca);
  
  return ConstantInt::get(theContext, APInt(32, 0));
}

Value* BInicijalizacijaSaDodelom::codegen() const {
  Value *r = _i->codegen();
  /* Ako promenljiva nije alocirana, alociramo je */
  if (!namedValues.count(_l) and !boolNamedValues.count(_l))
    boolNamedValues[_l] = createBEntryBlockAlloca(m, _l);
  else{
	  cerr << "Promenljiva "<< _l <<" je vec deklarisana." << endl;
	  exit(EXIT_FAILURE);
  }
  AllocaInst* alloca = boolNamedValues[_l];
  /* Cuvanje vrednosti */
  builder.CreateStore(r, alloca);
  
  return ConstantInt::get(theContext, APInt(32, 0));
}

Value* Blok::codegen() const {
  for (unsigned i = 0; i < _v.size() ; i++)
    _v[i]->codegen();
  return ConstantInt::get(theContext, APInt(32, 0));
}

Value* NaredbaIfThen::codegen() const {

  Value* condV = _i->codegen();
  if (!condV)
    return nullptr;
  
  Function* theFunction = builder.GetInsertBlock()->getParent();

  BasicBlock *thenBB = BasicBlock::Create(theContext, "then", theFunction);
  BasicBlock *mergeBB = BasicBlock::Create(theContext, "ifcont");

  builder.CreateCondBr(condV, thenBB, mergeBB);

  builder.SetInsertPoint(thenBB);
  Value* thenV = _n1->codegen();
  if (!thenV)
    return nullptr;
  builder.CreateBr(mergeBB);
  thenBB = builder.GetInsertBlock();

  theFunction->getBasicBlockList().push_back(mergeBB);
  builder.SetInsertPoint(mergeBB);

  return ConstantInt::get(theContext, APInt(32, 0));
}

Value* NaredbaIfThenElse::codegen() const {
  Value* condV = _i->codegen();
  if (!condV)
    return nullptr;
  
  Function* theFunction = builder.GetInsertBlock()->getParent();

  BasicBlock *thenBB = BasicBlock::Create(theContext, "then", theFunction);
  BasicBlock *elseBB = BasicBlock::Create(theContext, "else");
  BasicBlock *mergeBB = BasicBlock::Create(theContext, "ifcont");

  builder.CreateCondBr(condV, thenBB, elseBB);

  builder.SetInsertPoint(thenBB);
  Value* thenV = _n1->codegen();
  if (!thenV)
    return nullptr;
  builder.CreateBr(mergeBB);
  thenBB = builder.GetInsertBlock();

  theFunction->getBasicBlockList().push_back(elseBB);
  builder.SetInsertPoint(elseBB);
  Value* elseV = _n2->codegen();
  if (!elseV)
    return nullptr;
  builder.CreateBr(mergeBB);
  elseBB = builder.GetInsertBlock();

  theFunction->getBasicBlockList().push_back(mergeBB);
  builder.SetInsertPoint(mergeBB);

  return ConstantInt::get(theContext, APInt(32, 0));
}

Value* NaredbaWhile::codegen() const {

  Function* theFunction = builder.GetInsertBlock()->getParent();

  BasicBlock *loopBB = BasicBlock::Create(theContext, "loop", theFunction);
  builder.CreateBr(loopBB);

  builder.SetInsertPoint(loopBB);

  
  Value* stopV = _i->codegen();
  if (!stopV)
    return nullptr;

  BasicBlock *loopBB1 = BasicBlock::Create(theContext, "loop1", theFunction);
  BasicBlock *afterLoopBB = BasicBlock::Create(theContext, "afterloop", theFunction);
  builder.CreateCondBr(stopV, loopBB1, afterLoopBB);

  builder.SetInsertPoint(loopBB1);  
  if (!_n1->codegen())
    return nullptr;

  builder.CreateBr(loopBB);
  
  builder.SetInsertPoint(afterLoopBB);
  
  return ConstantInt::get(theContext, APInt(32, 0));
}
