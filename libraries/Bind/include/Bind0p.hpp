#ifndef BIND0P_H_
# define BIND0P_H_

# include	<typeinfo>
# include	"Bind.hpp"

///////////////
// Functions //
///////////////

template <typename Ret>
class Function<Ret (*)()>
{
  typedef	Ret (*Func)();
public:
  Function(Ret (*f)(void)) :
  _func(f)
  {

  }
  virtual ~Function() {};
  Ret	operator()()
  {
    return (_func());
  }
  Function(const Function &src) : _func(src._func) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      _func = src._func;
    return (*this);
  }

protected:
  Func	_func;
};

template <>
class Function<void (*)()>
{
  typedef	void (*Func)();
public:
  Function(void (*f)(void)) :
  _func(f)
  {

  }
  virtual ~Function() {};
  void	operator()()
  {
    _func();
  }
  Function(const Function &src) : _func(src._func) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      _func = src._func;
    return (*this);
  }

protected:
  Func	_func;
};


//////////////////////
// Member Functions //
/////////////////////


template <typename Ret, class C>
class Function<Ret (C::*)()>
{
  typedef	Ret (C::*Func)();
public:
  Function(Ret (C::*f)()) :
  _func(f), _inst(0)
  {

  }
  Function(Ret (C::*f)(void), C *inst) :
  _func(f), _inst(inst)
  {

  }
  virtual ~Function() {};
  Ret	operator()()
  {
    return ((_inst->*_func)());
  }
  Ret	operator()(C *inst)
  {
    return ((inst->*_func)());
  }
  Function(const Function &src) : _func(src._func), _inst(src._inst) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_inst = src._inst;
      }
    return (*this);
  }

protected:
  Func	_func;
  C	*_inst;
};

template <class C>
class Function<void (C::*)()>
{
  typedef	void (C::*Func)();
public:
  Function(void (C::*f)(void)) :
    _func(f), _inst(0)
  {

  }
  Function(void (C::*f)(void), C *inst) :
    _func(f), _inst(inst)
  {

  }
  virtual ~Function() {};
  void	operator()()
  {
    if (_inst != 0)
      (_inst->*_func)();
  }
  void	operator()(C *inst)
  {
    (inst->*_func)();
  }
  Function(const Function &src) : _func(src._func), _inst(src._inst) {}
  Function	&operator=(const Function &src)
  {
    if (&src != this)
      {
	_func = src._func;
	_inst = src._inst;
      }
    return (*this);
  }

protected:
  Func	_func;
  C	*_inst;
};

#endif /* BIND0P_H_ */
