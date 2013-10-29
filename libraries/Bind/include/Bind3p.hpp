#ifndef BIND3P_H_
# define BIND3P_H_

# include	<typeinfo>
# include	"Bind.hpp"

template <typename Ret, typename P1, typename P2, typename P3>
class Function<Ret, P1, P2, P3, void>
{
  typedef Ret	(*Func)(P1, P2, P3);
public:
  Function(Func f, P1 _1, P2 _2, P3 _3):
    _func(f), _1(_1), _2(_2), _3(_3)
  {

  }
  virtual ~Function() {}

  Ret	        operator()()
  {
    return (_func(_1, _2, _3));
  }

public:
  Function(const Function &src) : _func(src._func),
				  _1(src._1), _2(src._2),
				  _3(src._3)
  {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_1 = src._1;
	_2 = src._2;
	_3 = src._3;
      }
    return (*this);
  }

protected:
  Func	_func;
  P1	_1;
  P2	_2;
  P3	_3;
};

template <typename P1, typename P2, typename P3>
class Function<void, P1, P2, P3>
{
  typedef void	(*Func)(P1, P2, P3);
public:
  Function(Func f, P1 _1, P2 _2, P3 _3):
    _func(f), _1(_1), _2(_2), _3(_3)
  {

  }
  virtual ~Function() {}
  void		operator()()
  {
    _func(_1, _2, _3);
  }

public:
  Function(const Function &src) : _func(src._func),
				  _1(src._1), _2(src._2),
				  _3(src._3)
  {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_1 = src._1;
	_2 = src._2;
	_3 = src._3;
      }
    return (*this);
  }

protected:
  Func	_func;
  P1	_1;
  P2	_2;
  P3	_3;
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
