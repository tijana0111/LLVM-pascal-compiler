#ifndef __NAREDBA_HPP__
#define __NAREDBA_HPP__ 1
#include <string>
#include "izraz.hpp"
#include "codegen.hpp"
#include <vector>

using namespace std;

class Naredba {
public:
  virtual ~Naredba()
  { }
  virtual Value* codegen() const = 0;
};

class IspisIzraza : public Naredba {
public:
  IspisIzraza(Izraz *i)
    : _i(i->klon())
  {}
  ~IspisIzraza();
  IspisIzraza(const IspisIzraza &n);
  IspisIzraza& operator=(const IspisIzraza &n);
  Value* codegen() const;
private:
  Izraz* _i;
};

class IspisLIzraza : public Naredba {
public:
  IspisLIzraza(Izraz *i)
    : _i(i->klon())
  {}
  ~IspisLIzraza();
  IspisLIzraza(const IspisLIzraza &n);
  IspisLIzraza& operator=(const IspisLIzraza &n);
  Value* codegen() const;
private:
  Izraz* _i;
};

class Dodela : public Naredba {
public:
  Dodela(string l, Izraz* i)
    : _l(l), _i(i->klon())
  {}
  ~Dodela();
  Dodela(const Dodela& n);
  Dodela& operator=(const Dodela& n);
  Value* codegen() const;
private:
  string _l;
  Izraz* _i;
};

class BDodela : public Naredba {
public:
  BDodela(string l, Izraz* i)
    : _l(l), _i(i->klon())
  {}
  ~BDodela();
  BDodela(const BDodela& n);
  BDodela& operator=(const BDodela& n);
  Value* codegen() const;
private:
  string _l;
  Izraz* _i;
};

class Inicijalizacija : public Naredba {
public:
  Inicijalizacija(string l)
    : _l(l)
  {}
  Value* codegen() const;
private:
  string _l;
};

class InicijalizacijaSaDodelom : public Naredba {
public:
  InicijalizacijaSaDodelom(string l, Izraz* i)
    : _l(l), _i(i->klon())
  {}
  ~InicijalizacijaSaDodelom();
  InicijalizacijaSaDodelom(const InicijalizacijaSaDodelom& n);
  InicijalizacijaSaDodelom& operator=(const InicijalizacijaSaDodelom& n);
  Value* codegen() const;
private:
  string _l;
  Izraz* _i;
};

class BInicijalizacija : public Naredba {
public:
  BInicijalizacija(string l)
    : _l(l)
  {}
  Value* codegen() const;
private:
  string _l;
};

class BInicijalizacijaSaDodelom : public Naredba {
public:
  BInicijalizacijaSaDodelom(string l, Izraz* i)
    : _l(l), _i(i->klon())
  {}
  ~BInicijalizacijaSaDodelom();
  BInicijalizacijaSaDodelom(const BInicijalizacijaSaDodelom& n);
  BInicijalizacijaSaDodelom& operator=(const BInicijalizacijaSaDodelom& n);
  Value* codegen() const;
private:
  string _l;
  Izraz* _i;
};

class Blok : public Naredba {
public:
  Blok(vector<Naredba *> v)
    : _v(v)
  {}
  ~Blok();
  Value* codegen() const;
private:
  Blok(const Blok &n);
  Blok& operator=(const Blok &n);
  vector<Naredba *> _v;
};

class NaredbaIfThen : public Naredba {
public:
  NaredbaIfThen(Izraz* i, Naredba* n1)
    : _i(i->klon()), _n1(n1)
  {}
  ~NaredbaIfThen();
  Value* codegen() const;
private:
  NaredbaIfThen(const NaredbaIfThen &n);
  NaredbaIfThen& operator=(const NaredbaIfThen &n);
  Izraz* _i;
  Naredba* _n1;
};

class NaredbaIfThenElse : public Naredba {
public:
  NaredbaIfThenElse(Izraz* i, Naredba* n1, Naredba* n2)
    : _i(i->klon()), _n1(n1), _n2(n2)
  {}
  ~NaredbaIfThenElse();
  Value* codegen() const;
private:
  NaredbaIfThenElse(const NaredbaIfThenElse &n);
  NaredbaIfThenElse& operator=(const NaredbaIfThenElse &n);
  Izraz* _i;
  Naredba* _n1;
  Naredba* _n2;
};

class NaredbaWhile : public Naredba {
public:
  NaredbaWhile(Izraz* i, Naredba* n1)
    : _i(i->klon()), _n1(n1)
  {}
  ~NaredbaWhile();
  Value* codegen() const;
private:
  NaredbaWhile(const NaredbaWhile &n);
  NaredbaWhile& operator=(const NaredbaWhile &n);
  Izraz* _i;
  Naredba* _n1;
};

#endif

