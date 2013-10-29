#ifndef BIND0P_H_
# define BIND0P_H_

# include	<typeinfo>
# include	"Bind.hpp"

template <typename Ret>
class Bind0p
{
  typedef	Ret (*Func)();
public:
  Bind0p(Ret (*f)(void)) :
  _func(f)
  {

  }
  virtual ~Bind0p() {};
  Ret	operator()()
  {
    return (_func());
  }

protected:
  Func	_func;
};

template <>
void	Bind0p<void>::operator()()
{
  _func();
}

#endif /* BIND0P_H_ */
