#ifndef CALLBACK_H_
# define CALLBACK_H_

# if defined(DEBUG)
#  include	<stdexcept>
# endif //!DEBUG

# include	"ICallbacks.hh"

template <class C, class P0>
class Callback : public ICallbacks
{
public:
  Callback(C *self, P0 p, void (C::*func)(P0)) :
    _callback(func), _param(p), _self(self)
  {

  }

  virtual ~Callback() {};

public:
  void	operator()()
  {
#if defined(DEBUG)
    if (_self == 0)
      throw std::runtime_error("Callback: _self == 0");
#endif
    (_self->*_callback)(_param);
  }

private:
  Callback(Callback const&);
  Callback& operator=(Callback const&);

protected:
  void				(C::*_callback)(P0);
  P0				_param;
  C				*_self;
};

template <class P0>
class ApplicationCallback : public IApplicationCallbacks
{
public:
  ApplicationCallback(P0 p, void (Application::*func)(P0)) :
    _callback(func), _param(p)
  {

  }

  virtual ~ApplicationCallback() {};

public:
  void	operator()(Application *self)
  {
#if defined(DEBUG)
    if (self == 0)
      throw std::runtime_error("Callback: self == 0");
#endif
    (self->*_callback)(_param);
  }

private:
  ApplicationCallback(ApplicationCallback const&);
  ApplicationCallback& operator=(ApplicationCallback const&);

protected:
  void				(Application::*_callback)(P0);
  P0				_param;
};

#endif /* CALLBACK_H_ */
