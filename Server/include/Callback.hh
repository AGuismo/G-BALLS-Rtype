#ifndef CALLBACK_H_
# define CALLBACK_H_

# include	"ICallbacks.hh"
# include	"Bind.hpp"

template <class C, class P0>
class Callback : public ICallbacks
{
public:
  Callback(C *self, P0 *p, void (C::*func)(P0 *)) :
    _callback(func), _param(p), _self(self)
  {

  }
  virtual ~Callback() {};

public:
  void	operator()()
  {
	(_self->*_callback)(_param);
  }

private:
  Callback(Callback const&);
  Callback& operator=(Callback const&);

protected:
  void				(C::*_callback)(P0 *);
  P0					*_param;
  C					*_self;
};

#endif /* CALLBACK_H_ */
