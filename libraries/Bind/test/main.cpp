#include	<random>
#include	<iostream>
#include	<vector>
#include	"Bind.hpp"

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

int		main()
{
  Function<void>	foo = Func::Bind(&::_foo);
  Function<int>		fooRet = Func::Bind(&::_fooRet);
  Function<void, int>	foo1p = Func::Bind(&::_foo1p, 10);
  Function<int, int>	fooRet1p = Func::Bind(&::_fooRet1p, 20);

  foo();
  std::cout << "Retval: " << fooRet() << std::endl;
  foo1p();
  std::cout << "Retval: " << fooRet1p() << std::endl;
  return (0);
}
