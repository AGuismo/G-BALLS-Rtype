#ifndef BIND4P_H_
# define BIND4P_H_

# include	<typeinfo>
# include	"Bind.hpp"

///////////////
// Functions //
///////////////

template <typename Ret, typename P1, typename P2, typename P3,
	  typename P4>
class Function<Ret (*)(P1, P2, P3, P4)>
{
  typedef Ret	(*Func)(P1, P2, P3, P4);
public:
  Function(Func f, P1 _1, P2 _2, P3 _3, P4 _4):
    _func(f), _1(_1), _2(_2), _3(_3), _4(_4)
  {

  }

  Function(Func f):
    _func(f)
  {

  }

  virtual ~Function() {}

  Ret	        operator()()
  {
    return (_func(_1, _2, _3, _4));
  }

  Ret	        operator()(P1 p1, P2 p2, P3 p3, P4 p4)
  {
    return (_func(p1, p2, p3, p4));
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
class Function<void (*)(P1, P2, P3, P4)>
{
  typedef void	(*Func)(P1, P2, P3, P4);
public:
  Function(Func f, P1 _1, P2 _2, P3 _3, P4 _4):
    _func(f), _1(_1), _2(_2), _3(_3), _4(_4)
  {

  }

  Function(Func f):
    _func(f)
  {

  }

  virtual ~Function() {}
  void		operator()()
  {
    _func(_1, _2, _3, _4);
  }

  void		operator()(P1 p1, P2 p2, P3 p3, P4 p4)
  {
    _func(p1, p2, p3, p4);
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

//////////////////////
// Member Functions //
/////////////////////

template <typename Ret, class C, typename P1, typename P2, typename P3, typename P4>
class Function<Ret (C::*)(P1, P2, P3, P4)>
{
  typedef	Ret (C::*Func)(P1, P2, P3, P4);
public:
  Function(Func f, P1 _1, P2 _2, P3 _3, P4 _4) :
    _func(f), _inst(0), _1(_1), _2(_2), _3(_3), _4(_4)
  {

  }
  Function(Func f, C *inst, P1 _1, P2 _2, P3 _3, P4 _4) :
    _func(f), _inst(inst), _1(_1), _2(_2), _3(_3), _4(_4)
  {

  }

  Function(Func f) :
    _func(f), _inst(0)
  {

  }
  Function(Func f, C *inst) :
    _func(f), _inst(inst)
  {

  }

  virtual ~Function() {};
  Ret	operator()(P1 p1, P2 p2, P3 p3, P4 p4)
  {
    if (_inst != 0)
      return ((_inst->*_func)(p1, p2, p3, p4));
  }
  Ret	operator()(C *inst, P1 p1, P2 p2, P3 p3, P4 p4)
  {
    return ((inst->*_func)(p1, p2, p3, p4));
  }

  Ret	operator()()
  {
    if (_inst != 0)
      return ((_inst->*_func)(_1, _2, _3, _4));
  }
  Ret	operator()(C *inst)
  {
    return ((inst->*_func)(_1, _2, _3, _4));
  }

  Function(const Function &src) : _func(src._func), _inst(src._inst),
				  _1(src._1), _2(src._2),
				  _3(src._3), _4(src._4) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_inst = src._inst;
	_1 = src._1;
	_2 = src._2;
	_3 = src._3;
	_4 = src._4;
      }
    return (*this);
  }

protected:
  Func	_func;
  C	*_inst;
  P1	_1;
  P2	_2;
  P3	_3;
  P4	_4;
};

template <class C, typename P1, typename P2, typename P3, typename P4>
class Function<void (C::*)(P1, P2, P3, P4)>
{
  typedef	void (C::*Func)(P1, P2, P3, P4);
public:
  Function(Func f, P1 _1, P2 _2, P3 _3, P4 _4) :
    _func(f), _inst(0), _1(_1), _2(_2), _3(_3), _4(_4)
  {

  }

  Function(Func f, C *inst, P1 _1, P2 _2, P3 _3, P4 _4) :
    _func(f), _inst(inst), _1(_1), _2(_2), _3(_3), _4(_4)
  {

  }

  Function(Func f) :
    _func(f), _inst(0)
  {

  }

  Function(Func f, C *inst) :
    _func(f), _inst(inst)
  {

  }

  virtual ~Function() {};
  void	operator()()
  {
    if (_inst != 0)
      (_inst->*_func)(_1, _2, _3, _4);
  }
  void	operator()(C *inst)
  {
    (inst->*_func)(_1, _2, _3, _4);
  }

  void	operator()(P1 p1, P2 p2, P3 p3, P4 p4)
  {
    if (_inst != 0)
      (_inst->*_func)(p1, p2, p3, p4);
  }
  void	operator()(C *inst, P1 p1, P2 p2, P3 p3, P4 p4)
  {
    (inst->*_func)(p1, p2, p3, p4);
  }
  Function(const Function &src) : _func(src._func), _inst(src._inst),
				  _1(src._1), _2(src._2),
				  _3(src._3), _4(src._4) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_inst = src._inst;
	_1 = src._1;
	_2 = src._2;
	_3 = src._3;
	_4 = src._4;
      }
    return (*this);
  }

protected:
  Func	_func;
  C	*_inst;
  P1	_1;
  P2	_2;
  P3	_3;
  P4	_4;
};

#endif /* BIND1P_H_ */
