#ifndef BIND1P_H_
# define BIND1P_H_

# include	<typeinfo>
# include	"Bind.hpp"

///////////////
// Functions //
///////////////

template <typename Ret, typename P1>
class Function<Ret (*)(P1)>
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
  Ret	        operator()(P1 p1)
  {
    return (_func(p1));
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
class Function<void (*)(P1)>
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
  void	        operator()(P1 p1)
  {
    _func(p1);
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

//////////////////////
// Member Functions //
/////////////////////


template <typename Ret, class C, typename P1>
class Function<Ret (C::*)(P1)>
{
  typedef	Ret (C::*Func)(P1);
public:
  Function(Ret (C::*f)(P1), P1 _1) :
    _func(f), _inst(0), _1(_1)
  {

  }
  Function(Ret (C::*f)(P1)) :
    _func(f), _inst(0)
  {

  }
  Function(Ret (C::*f)(P1), C *inst, P1 _1) :
  _func(f), _inst(inst), _1(_1)
  {

  }
  virtual ~Function() {};
  Ret	operator()()
  {
    if (_inst != 0)
      return ((_inst->*_func)(_1));
  }
  Ret	operator()(P1 p1)
  {
    if (_inst != 0)
      return ((_inst->*_func)(p1));
  }
  Ret	operator()(C *inst)
  {
    return ((inst->*_func)(_1));
  }
  Ret	operator()(C *inst, P1 p1)
  {
    return ((inst->*_func)(p1));
  }
  Function(const Function &src) : _func(src._func), _inst(src._inst),
				  _1(src._1) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_inst = src._inst;
	_1 = src._1;
      }
    return (*this);
  }

protected:
  Func	_func;
  C	*_inst;
  P1	_1;
};

template <class C, typename P1>
class Function<void (C::*)(P1)>
{
  typedef	void (C::*Func)(P1);
public:
  Function(void (C::*f)(P1)) :
    _func(f), _inst(0)
  {

  }
  Function(void (C::*f)(P1), P1 _1) :
    _func(f), _inst(0), _1(_1)
  {

  }
  Function(void (C::*f)(P1), C *inst, P1 _1) :
    _func(f), _inst(inst), _1(_1)
  {

  }
  virtual ~Function() {};
  void	operator()()
  {
    if (_inst != 0)
      (_inst->*_func)(_1);
  }
  void	operator()(P1 p1)
  {
    if (_inst != 0)
      (_inst->*_func)(p1);
  }
  void	operator()(C *inst)
  {
    (inst->*_func)(_1);
  }
  void	operator()(C *inst, P1 p1)
  {
    (inst->*_func)(p1);
  }
  Function(const Function &src) : _func(src._func), _inst(src._inst),
				  _1(src._1) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_inst = src._inst;
	_1 = src._1;
      }
    return (*this);
  }

protected:
  Func	_func;
  C	*_inst;
  P1	_1;
};

#endif /* BIND1P_H_ */
