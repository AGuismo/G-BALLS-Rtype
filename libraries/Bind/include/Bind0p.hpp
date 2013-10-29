#ifndef BIND0P_H_
# define BIND0P_H_

# include	<typeinfo>
# include	"Bind.hpp"

template <typename Ret>
class Function<Ret>
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
class Function<void>
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

#endif /* BIND0P_H_ */
