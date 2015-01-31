#ifndef BIND2P_H_
# define BIND2P_H_

# include	<typeinfo>
# include	"Bind.hpp"

///////////////
// Functions //
///////////////

template <typename Ret, typename P1, typename P2>
class Function<Ret (*)(P1, P2)>
{
  typedef Ret	(*Func)(P1, P2);
public:
  Function(Func f, P1 _1, P2 _2):
    _func(f), _1(_1), _2(_2)
  {

  }

  Function(Func f):
    _func(f)
  {

  }

  virtual ~Function() {}

  Ret	        operator()()
  {
    return (_func(_1, _2));
  }

  Ret	        operator()(P1 p1, P2 p2)
  {
    return (_func(p1, p2));
  }

public:
  Function(const Function &src) : _func(src._func), _1(src._1), _2(src._2) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_1 = src._1;
	_2 = src._2;
      }
    return (*this);
  }

protected:
  Func	_func;
  P1	_1;
  P2	_2;
};

template <typename P1, typename P2>
class Function<void (*)(P1, P2)>
{
  typedef void	(*Func)(P1, P2);
public:
  Function(Func f, P1 _1, P2 _2):
    _func(f), _1(_1), _2(_2)
  {

  }

  Function(Func f):
    _func(f)
  {

  }

  virtual ~Function() {}
  void		operator()()
  {
    _func(_1, _2);
  }

  void	        operator()(P1 p1, P2 p2)
  {
    _func(p1, p2);
  }
public:
  Function(const Function &src) : _func(src._func), _1(src._1), _2(src._2) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_1 = src._1;
	_2 = src._2;
      }
    return (*this);
  }

protected:
  Func	_func;
  P1	_1;
  P2	_2;
};

//////////////////////
// Member Functions //
/////////////////////

template <typename Ret, class C, typename P1, typename P2>
class Function<Ret (C::*)(P1, P2)>
{
  typedef	Ret (C::*Func)(P1, P2);
public:
  Function(Ret (C::*f)(P1, P2), P1 _1, P2 _2) :
    _func(f), _inst(0), _1(_1), _2(_2)
  {

  }

  Function(Ret (C::*f)(P1, P2), C *inst, P1 _1, P2 _2) :
    _func(f), _inst(inst), _1(_1), _2(_2)
  {

  }

  Function(void (C::*f)(P1, P2)) :
    _func(f), _inst(0)
  {

  }
  Function(void (C::*f)(P1, P2), C *inst) :
    _func(f), _inst(inst)
  {

  }

  virtual ~Function() {};
  Ret	operator()()
  {
    if (_inst != 0)
      return ((_inst->*_func)(_1, _2));
  }

  Ret	operator()(C *inst)
  {
    return ((inst->*_func)(_1, _2));
  }

  Ret	operator()(P1 p1, P2 p2)
  {
    if (_inst != 0)
      return ((_inst->*_func)(p1, p2));
  }

  Ret	operator()(C *inst, P1 p1, P2 p2)
  {
    return ((inst->*_func)(p1, p2));
  }

  Function(const Function &src) : _func(src._func), _inst(src._inst),
				  _1(src._1), _2(src._2) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_inst = src._inst;
	_1 = src._1;
	_2 = src._2;
      }
    return (*this);
  }

protected:
  Func	_func;
  C	*_inst;
  P1	_1;
  P2	_2;
};

template <class C, typename P1, typename P2>
class Function<void (C::*)(P1, P2)>
{
  typedef	void (C::*Func)(P1, P2);
public:
  Function(void (C::*f)(P1, P2), P1 _1, P2 _2) :
    _func(f), _inst(0), _1(_1), _2(_2)
  {

  }
  Function(void (C::*f)(P1, P2), C *inst, P1 _1, P2 _2) :
    _func(f), _inst(inst), _1(_1), _2(_2)
  {

  }

  Function(void (C::*f)(P1, P2)) :
    _func(f), _inst(0)
  {

  }
  Function(void (C::*f)(P1, P2), C *inst) :
    _func(f), _inst(inst)
  {

  }

  virtual ~Function() {};
  void	operator()()
  {
    if (_inst != 0)
      (_inst->*_func)(_1, _2);
  }

  void	operator()(C *inst)
  {
    (inst->*_func)(_1, _2);
  }

  void	operator()(P1 p1, P2 p2)
  {
    if (_inst != 0)
      (_inst->*_func)(p1, p2);
  }

  void	operator()(C *inst, P1 p1, P2 p2)
  {
    (inst->*_func)(p1, p2);
  }

  Function(const Function &src) : _func(src._func), _inst(src._inst),
				  _1(src._1), _2(src._2) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_inst = src._inst;
	_1 = src._1;
	_2 = src._2;
      }
    return (*this);
  }

protected:
  Func	_func;
  C	*_inst;
  P1	_1;
  P2	_2;
};

#endif /* BIND1P_H_ */
