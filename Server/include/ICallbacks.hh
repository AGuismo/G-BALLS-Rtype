#ifndef ICALLBACKS_H_
# define ICALLBACKS_H_

class	Application;

class ICallbacks
{
public:
  virtual ~ICallbacks() {};

public:
  virtual void	operator()(Application *) = 0;
};

#endif /* ICALLBACKS_H_ */
