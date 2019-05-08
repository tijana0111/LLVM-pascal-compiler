#ifndef __IZRAZ_HPP__ 
#define __IZRAZ_HPP__ 1

#include <iostream>
#include <string>
#include <map>
#include <cstdlib>
#include "codegen.hpp"
using namespace std;

class Izraz {
public:
  virtual Izraz* klon() const = 0;
  virtual ~Izraz() {

  }
  virtual Value* codegen() const = 0;
};

class Konstanta : public Izraz {
public:
  Konstanta(int c)
    :_c(c)
  {}
  Izraz* klon() const;
  Value* codegen() const;
private:
  int _c;
};

class TrueKonstanta : public Izraz {
public:
  TrueKonstanta()
  {}
  Izraz* klon() const;
  Value* codegen() const;
};

class FalseKonstanta : public Izraz {
public:
  FalseKonstanta()
  {}
  Izraz* klon() const;
  Value* codegen() const;
};

class Promenljiva : public Izraz {
public:
  Promenljiva(string ime)
    :_ime(ime)
  {}
  Izraz* klon() const;
  Value* codegen() const;
private:
  string _ime;
};

class BPromenljiva : public Izraz {
public:
  BPromenljiva(string ime)
    :_ime(ime)
  {}
  Izraz* klon() const;
  Value* codegen() const;
private:
  string _ime;
};

class BinOperator : public Izraz {
public:
  BinOperator(Izraz* levi, Izraz* desni)
    :_levi(levi->klon()), _desni(desni->klon())
  {}
  ~BinOperator ();
  BinOperator(const BinOperator& z);
  BinOperator& operator=(const BinOperator& z);
protected:  
  Izraz* _levi;
  Izraz* _desni;
};

class Zbir : public BinOperator {
public:
  Zbir(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  Izraz* klon() const;
  Value* codegen() const;
};

class Razlika : public BinOperator {
public:
  Razlika(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  Izraz* klon() const ;
  Value* codegen() const;
};

class Proizvod : public BinOperator {
public:
  Proizvod(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  Izraz* klon() const;
  Value* codegen() const;
};

class Kolicnik : public BinOperator {
public:
  Kolicnik(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  Izraz* klon() const ;
  Value* codegen() const;
};

class Mod : public BinOperator {
public:
  Mod(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  Izraz* klon() const ;
  Value* codegen() const;
};

class Minus : public Izraz{
public:
  Minus(Izraz* i)
    :_i(i)
  {}
  ~Minus ();
  Minus(const Minus& z);
  Minus& operator=(const Minus& z);
  Izraz* klon() const;
  Value* codegen() const;
private:
  Izraz *_i;
};

class Vece : public BinOperator {
public:
  Vece(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  Izraz* klon() const;
  Value* codegen() const;
};

class Manje : public BinOperator {
public:
  Manje(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  Izraz* klon() const;
  Value* codegen() const;
};


class IzrazAnd : public BinOperator {
public:
  IzrazAnd(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  Izraz* klon() const ;
  Value* codegen() const;
};

class IzrazOr : public BinOperator {
public:
  IzrazOr(Izraz* i1, Izraz* i2)
    :BinOperator(i1, i2)
  {}
  Izraz* klon() const;
  Value* codegen() const;
};

class IzrazNot : public Izraz{
public:
  IzrazNot(Izraz* i)
    :_i(i)
  {}
  ~IzrazNot ();
  IzrazNot(const IzrazNot& z);
  IzrazNot& operator=(const IzrazNot& z);
  Izraz* klon() const;
  Value* codegen() const;
private:
	Izraz *_i;
};
#endif
