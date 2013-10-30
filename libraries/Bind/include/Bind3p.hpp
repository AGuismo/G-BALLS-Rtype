#ifndef BIND3P_H_
# define BIND3P_H_

# include	<typeinfo>
# include	"Bind.hpp"

///////////////
// Functions //
///////////////

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

//////////////////////
// Member Functions //
/////////////////////

template <typename Ret, class C, typename P1, typename P2, typename P3>
class Function<Ret (C::*)(P1, P2, P3)>
{
  typedef	Ret (C::*Func)(P1, P2, P3);
public:
  Function(Func f, P1 _1, P2 _2, P3 _3) :
    _func(f), _inst(0), _1(_1), _2(_2), _3(_3)
  {

  }
  Function(Func f, C *inst, P1 _1, P2 _2, P3 _3) :
    _func(f), _inst(inst), _1(_1), _2(_2), _3(_3)
  {

  }
  virtual ~Function() {};
  Ret	operator()()
  {
    if (_inst != 0)
      return ((_inst->*_func)(_1, _2, _3));
  }
  Ret	operator()(C *inst)
  {
    return ((inst->*_func)(_1, _2, _3));
  }
  Function(const Function &src) : _func(src._func), _inst(src._inst),
				  _1(src._1), _2(src._2),
				  _3(src._3) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_inst = src._inst;
	_1 = src._1;
	_2 = src._2;
	_3 = src._3;
      }
    return (*this);
  }

protected:
  Func	_func;
  C	*_inst;
  P1	_1;
  P2	_2;
  P3	_3;
};

template <class C, typename P1, typename P2, typename P3>
class Function<void (C::*)(P1, P2, P3)>
{
  typedef	void (C::*Func)(P1, P2, P3);
public:
  Function(Func f, P1 _1, P2 _2, P3 _3) :
    _func(f), _inst(0), _1(_1), _2(_2), _3(_3)
  {

  }
  Function(Func f, C *inst, P1 _1, P2 _2, P3 _3) :
    _func(f), _inst(inst), _1(_1), _2(_2), _3(_3)
  {

  }
  virtual ~Function() {};
  void	operator()()
  {
    if (_inst != 0)
      (_inst->*_func)(_1, _2, _3);
  }
  void	operator()(C *inst)
  {
    (inst->*_func)(_1, _2, _3);
  }
  Function(const Function &src) : _func(src._func), _inst(src._inst),
				  _1(src._1), _2(src._2),
				  _3(src._3) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_inst = src._inst;
	_1 = src._1;
	_2 = src._2;
	_3 = src._3;
      }
    return (*this);
  }

protected:
  Func	_func;
  C	*_inst;
  P1	_1;
  P2	_2;
  P3	_3;
};

#endif /* BIND1P_H_ */
