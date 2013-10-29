//
// ThreadWork.hpp for thread in /home/lamber_k/module_4e_sem/plazza/plazza
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Tue Apr 16 11:56:49 2013 lambert kevin
// Last update Sun Apr 21 00:39:03 2013 lambert kevin
//

#ifndef THREADWORK_HPP_
# define THREADWORK_HPP_

# include	"ThreadPlatform.hh"

namespace	Thread
{
  
  class		IWork
  {
  public:
	virtual ~IWork() {};
	virtual void	operator()() = 0;
  };

  template <typename Param>
  class		Work : public IWork
  {
    void	(*_func)(Param);
    Param	_arg;

  public:
    Work(void (*func)(Param), Param arg) : _func(func), _arg(arg) {}
	Work(const Work &src) : _func(src._func), _arg(src._arg) {}
	Work	&operator=(const Work &src)
	{
		if (&src != *this)
		{
			_func = src._func;
			_arg = src._arg;
		}
		return (*this);
	}
    virtual ~Work() {}
    void	operator()()
    {
      _func(_arg);
    }
  };

};

#endif /* THREADWORK_HPP_ */
