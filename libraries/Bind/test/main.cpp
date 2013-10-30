#include	<string>
#include	<random>
#include	<iostream>
#include	<vector>
#include	"Bind.hpp"

class	A
{
public:
  A(int p) : pony(p) {}
  int	run()
  {
    std::cout << __PRETTY_FUNCTION__ << ":" << pony << std::endl;
  }
  int	foo(int var)
  {
    std::cout << __PRETTY_FUNCTION__ << ":" << var << ":" << pony << std::endl;
  }
  int	foo(int var, double d)
  {
    std::cout << __PRETTY_FUNCTION__ << ":" << var << ":" << d << ":" << pony << std::endl;
  }
  int	foo(int var, double d, char c)
  {
    std::cout << __PRETTY_FUNCTION__ << ":" << var << ":" << d << ":"
	      << c << ":" << pony << std::endl;
  }
  int	bar(int var, double d, char c, std::string *s)
  {
    std::cout << __PRETTY_FUNCTION__ << ":" << var << ":" << d << ":"
	      << c << ":" << *s << ":" << pony << std::endl;
  }
  int	pony;
};

void	_foo()
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int	_fooRet()
{
  int	r = std::rand();

  std::cout << __PRETTY_FUNCTION__ << ":" << r << std::endl;
  return (r);
}

void	_foo1p(int a)
{
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  std::cout << "p1: " << a << std::endl;
}

int	_fooRet1p(int a)
{
  int	r = std::rand();

  std::cout << __PRETTY_FUNCTION__ << ":" << r << std::endl;
  std::cout << "p1: " << a << std::endl;
  return (r);
}

int					main()
{
  A							inst(10);
  A							inst2(42);
  std::string						s("Tesssst");
  Function<void (*)()>					foo = Func::Bind(&::_foo);
  Function<int (*)()>					fooRet = Func::Bind(&::_fooRet);
  Function<void (*)(int)>				foo1p = Func::Bind(&::_foo1p, 10);
  Function<int (*)(int)>				fooRet1p = Func::Bind(&::_fooRet1p, 20);
  Function<int (A::*)()>				fooClass = Func::Bind(&A::run, &inst);
  Function<int (A::*)()>				fooClass2 = Func::Bind(&A::run);
  Function<int (A::*)(int)>				fooClass1p = Func::Bind(&A::foo, &inst, 12);
  Function<int (A::*)(int)>				fooClass1p2 = Func::Bind(&A::foo, 23);
  Function<int (A::*)(int, double)>			fooClass2p = Func::Bind(&A::foo, &inst, 12,
										3.4);
  Function<int (A::*)(int, double)>			fooClass2p2 = Func::Bind(&A::foo, 23, 4.2);
  Function<int (A::*)(int, double, char)>		fooClass3p = Func::Bind(&A::foo, &inst, 12,
										3.4, 'a');
  Function<int (A::*)(int, double, char)>		fooClass3p2 = Func::Bind(&A::foo, 23, 4.2,
										 'b');
  Function<int (A::*)(int, double, char, std::string *)> fooClass4p = Func::Bind(&A::bar, &inst,
										 12, 3.4, 'a', &s);
  Function<int (A::*)(int, double, char, std::string *)> fooClass4p2 = Func::Bind(&A::bar, 23, 4.2,
										  'b', &s);

  foo();
  std::cout << "Retval: " << fooRet() << std::endl;
  foo1p();
  std::cout << "Retval: " << fooRet1p() << std::endl;
  fooClass();
  fooClass2(&inst2);
  fooClass1p();
  fooClass1p2(&inst2);
  fooClass2p();
  fooClass2p2(&inst2);
  fooClass3p();
  fooClass3p2(&inst2);
  fooClass4p();
  s = "Fils de Pute";
  fooClass4p();
  fooClass4p2(&inst2);
  return (0);
}
