#ifndef BIND4P_H_
# define BIND4P_H_

# include	<typeinfo>
# include	"Bind.hpp"

template <typename Ret, typename P1=void, typename P2=void, typename P3=void, typename P4=void>
class Function
{
  typedef Ret	(*Func)(P1, P2, P3, P4);
public:
  Function(Func f, P1 _1, P2 _2, P3 _3, P4 _4):
    _func(f), _1(_1), _2(_2), _3(_3), _4(_4)
  {

  }
  virtual ~Function() {}

  Ret	        operator()()
  {
    return (_func(_1, _2, _3, _4));
  }

public:
  Function(const Function &src) : _func(src._func),
				  _1(src._1), _2(src._2),
				  _3(src._3), _4(src._4)
  {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_1 = src._1;
	_2 = src._2;
	_3 = src._3;
	_4 = src._4;
      }
    return (*this);
  }

protected:
  Func	_func;
  P1	_1;
  P2	_2;
  P3	_3;
  P4	_4;
};

template <typename P1, typename P2, typename P3, typename P4>
class Function<void, P1, P2, P3, P4>
{
  typedef void	(*Func)(P1, P2, P3, P4);
public:
  Function(Func f, P1 _1, P2 _2, P3 _3, P4 _4):
    _func(f), _1(_1), _2(_2), _3(_3), _4(_4)
  {

  }
  virtual ~Function() {}
  void		operator()()
  {
    _func(_1, _2, _3, _4);
  }

public:
  Function(const Function &src) : _func(src._func),
				  _1(src._1), _2(src._2),
				  _3(src._3), _4(src._4)
  {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_1 = src._1;
	_2 = src._2;
	_3 = src._3;
	_4 = src._4;
      }
    return (*this);
  }

protected:
  Func	_func;
  P1	_1;
  P2	_2;
  P3	_3;
  P4	_4;
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
