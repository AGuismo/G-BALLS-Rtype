#ifndef LOADER_MANAGER_H_
# define LOADER_MANAGER_H_

#include	"Threads.hpp"
#include	"ThreadMutex.hh"
#include	"CheckFileAbstract.h"
#include	"DynamicAbstract.h"

namespace loglib
{
  class	Log;
}

class	AIaAlgo;

namespace	botLoader
{
  class		Manager
  {
  public:
    Manager(loglib::Log &log);
    ~Manager();

  public:
    typedef AIaAlgo	*(*instance_call)(void);

  public:
    void		initialize(std::string &);
    void		run();
    void		stop();

  private:
    bool		addNewIa(const std::string &path);
    bool		updateIa(const std::string &path);

  public:
    AIaAlgo		*getSimpleBydos(void);
    AIaAlgo		*getBossBydos(void);
    int			getSimpleBydosSize(void);
    int			getBossBydosSize(void);

  public:
    static void		routine(Manager *);

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);
  public:
    typedef	std::map<std::string, AIaAlgo *>	bydos_type;

  private:
    bool				_active;
    ICheckFileAbstract			*_checkFile;
    DynamicAbstract			*_dynLoader;
    bydos_type				_simpleBydos;
    bydos_type				_bossBydos;
    std::map<std::string, UPDATE>	*_upList;
    Threads<void (*)(Manager *)>	_th;
    Thread::Mutex			_lock;
    loglib::Log				&_log;
  };

}

#endif /* LOADER_MANAGER_H_ */
