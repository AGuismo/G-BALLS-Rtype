//
// ThreadWork.hpp for thread in /home/lamber_k/module_4e_sem/plazza/plazza
//
// Made by lambert kevin
// Login   <lamber_k@epitech.net>
//
// Started on  Tue Apr 16 11:56:49 2013 lambert kevin
// Last update Wed Oct 30 12:25:54 2013 lambert kevin
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

  template <typename Func>
  class		Work : public IWork
  {
    Function<Func>	_func;

  public:
    Work(Function<Func> f) : _func(f) {}
    Work(const Work &src) : _func(src._func) {}
    Work	&operator=(const Work &src)
    {
      if (&src != *this)
	{
	  _func = src._func;
	}
      return (*this);
    }
    virtual ~Work() {}
    void	operator()()
    {
      _func();
    }
  };

};

#endif /* THREADWORK_HPP_ */
