#include "izraz.hpp"
#include <map>
using namespace std;

extern map<string,  char> tablica;


Izraz* Konstanta::klon() const {
  return new Konstanta(*this);
}
Izraz* TrueKonstanta::klon() const {
  return new TrueKonstanta(*this);
}
Izraz* FalseKonstanta::klon() const {
  return new FalseKonstanta(*this);
}
Izraz* Promenljiva::klon() const {
  return new Promenljiva(*this);
}

Izraz* BPromenljiva::klon() const {
  return new BPromenljiva(*this);
}

BinOperator::~BinOperator () {
  delete _levi;
  delete _desni;
}

BinOperator::BinOperator(const BinOperator& z) {
  _levi = z._levi->klon();
  _desni = z._desni->klon();
}

BinOperator& BinOperator::operator=(const BinOperator& z) {
  if (this != &z) {
    delete _levi;
    delete _desni;
    _levi = z._levi->klon();
    _desni = z._desni->klon();
  }
  return *this;
}

Izraz* Zbir::klon() const {
  return new Zbir(*this);
}

Izraz* Razlika::klon() const {
  return new Razlika(*this);
}

Izraz* Proizvod::klon() const {
  return new Proizvod(*this);
}

Izraz* Kolicnik::klon() const {
  return new Kolicnik(*this);
}

Izraz* Mod::klon() const {
  return new Mod(*this);
}

Izraz* Vece::klon() const {
  return new Vece(*this);
}

Izraz* Manje::klon() const {
  return new Manje(*this);
}

Izraz* IzrazAnd::klon() const {
  return new IzrazAnd(*this);
}

Izraz* IzrazOr::klon() const {
  return new IzrazOr(*this);
}

Izraz* IzrazNot::klon() const {
  return new IzrazNot(*this);
}

IzrazNot::~IzrazNot() {
  delete _i;
}

IzrazNot::IzrazNot(const IzrazNot& z) {
  _i = z._i->klon();
}

IzrazNot& IzrazNot::operator=(const IzrazNot& z) {
  if (this != &z) {
    delete _i;
    _i = z._i->klon();
}
  return *this;
}

Izraz* Minus::klon() const {
  return new Minus(*this);
}

Minus::~Minus() {
  delete _i;
}

Minus::Minus(const Minus& z) {
  _i = z._i->klon();
}

Minus& Minus::operator=(const Minus& z) {
  if (this != &z) {
    delete _i;
    _i = z._i->klon();
}
  return *this;
}
/*********************** codegen **************************/

Value* Konstanta::codegen() const {
  return ConstantInt::get(theContext, APInt(32, _c));
}
Value* TrueKonstanta::codegen() const {
  return ConstantInt::get(theContext, APInt(1, 1));
}
Value* FalseKonstanta::codegen() const {
  return ConstantInt::get(theContext, APInt(1, 0));
}
Value* Promenljiva::codegen() const {
  AllocaInst *v = namedValues[_ime];
  if (!v) {
    cerr << "Nepostojeca promenljiva " << _ime << endl;
    return nullptr;
  }
  return builder.CreateLoad(Type::getInt32Ty(theContext), v, _ime.c_str());
}

Value* BPromenljiva::codegen() const {
  AllocaInst *v = boolNamedValues[_ime];
  if (!v) {
    cerr << "Nepostojeca bool promenljiva " << _ime << endl;
    return nullptr;
  }
  return builder.CreateLoad(Type::getInt1Ty(theContext), v, _ime.c_str());
}

Value* Zbir::codegen() const {
  Value *l = _levi->codegen();
  Value *r = _desni->codegen();
  return builder.CreateAdd(l, r, "tmpadd");
}

Value* Razlika::codegen() const {
  Value *l = _levi->codegen();
  Value *r = _desni->codegen();
  return builder.CreateSub(l, r, "tmpsub");
}

Value* Proizvod::codegen() const {
  Value *l = _levi->codegen();
  Value *r = _desni->codegen();
  return builder.CreateMul(l, r, "tmpmul");
}

Value* Kolicnik::codegen() const {
  Value *l = _levi->codegen();
  Value *r = _desni->codegen();
  return builder.CreateUDiv(l, r, "tmpdiv");
}

Value* Mod::codegen() const {
  Value *l = _levi->codegen();
  Value *r = _desni->codegen();
  return builder.CreateSRem(l, r, "tmpadd");
}

Value* Minus::codegen() const {
  Value *l = _i->codegen();
  if (l == NULL)
    return NULL;
  Value *r = ConstantInt::get(theContext, APInt(32, -1));
  return builder.CreateMul(l, r, "tmpmin");
}

Value* Vece::codegen() const {
  Value *l = _levi->codegen();
  Value *r = _desni->codegen();
  return builder.CreateICmpSGT(l, r, "tmpgt");
}

Value* Manje::codegen() const {
  Value *l = _levi->codegen();
  Value *r = _desni->codegen();
  return builder.CreateICmpSLT(l, r, "tmplt");
}

Value* IzrazAnd::codegen() const {
  Value *l = _levi->codegen();
  Value *r = _desni->codegen();
  if (l == NULL || r == NULL)
    return NULL;
  return builder.CreateAnd(l, r, "andtmp");
}

Value* IzrazOr::codegen() const {
  Value *l = _levi->codegen();
  Value *r = _desni->codegen();
  if (l == NULL || r == NULL)
    return NULL;
  return builder.CreateOr(l, r, "ortmp");
}

Value* IzrazNot::codegen() const {
  Value *l = _i->codegen();
  if (l == NULL)
    return NULL;
  return builder.CreateNot(l, "nottmp");
}
