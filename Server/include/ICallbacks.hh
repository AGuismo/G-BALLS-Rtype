#ifndef ICALLBACKS_H_
# define ICALLBACKS_H_

class Application;

class ICallbacks
{
public:
  virtual ~ICallbacks() {};

public:
  virtual void	operator()() = 0;
};

class IApplicationCallbacks
{
public:
  virtual ~IApplicationCallbacks() {};

public:

  virtual void	operator()(Application *self) = 0;
};

#endif /* ICALLBACKS_H_ */
