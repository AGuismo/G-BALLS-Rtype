#ifndef BIND1P_H_
# define BIND1P_H_

# include	<typeinfo>
# include	"Bind.hpp"

template <typename Ret, typename P1>
class Function<Ret, P1, void, void, void>
{
  typedef Ret	(*Func)(P1);
public:
  Function(Func f, P1 _1):
    _func(f), _1(_1)
  {

  }
  virtual ~Function() {}

  Ret	        operator()()
  {
    return (_func(_1));
  }

public:
  Function(const Function &src) : _func(src._func), _1(src._1) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_1 = src._1;
      }
    return (*this);
  }

protected:
  Func	_func;
  P1	_1;
};

template <typename P1>
class Function<void, P1>
{
  typedef void	(*Func)(P1);
public:
  Function(Func f, P1 _1):
    _func(f), _1(_1)
  {

  }
  virtual ~Function() {}
  void		operator()()
  {
    _func(_1);
  }

public:
  Function(const Function &src) : _func(src._func), _1(src._1) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_1 = src._1;
      }
    return (*this);
  }

protected:
  Func	_func;
  P1	_1;
};

// template <typename Ret, typename P1>
// class Bind1p
// {
// public:
//   Bind1p(Ret (*f)(P1), P1 _1):
//     _func(f), _1(_1)
//   {

//   }
//   virtual ~Bind1p() {}
//   virtual Ret	operator()()
//   {
//     return (_func(_1));
//   }

// protected:
//   Ret	(*_func)(P1);
//   P1	_1;
// };

// template <typename P1>
// class Bind1p<void, P1>
// {
// public:
//   Bind1p(void (*f)(P1), P1 _1):
//     _func(f), _1(_1)
//   {

//   }
//   virtual ~Bind1p() {}
//   virtual void	operator()()
//   {
//     _func(_1);
//   }

// protected:
//   void	(*_func)(P1);
//   P1	_1;

// };

#endif /* BIND1P_H_ */
