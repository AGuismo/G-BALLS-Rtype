#ifndef LOADER_MANAGER_H_
# define LOADER_MANAGER_H_

#include	"Threads.hpp"
#include	"ThreadMutex.hh"
#include	"CheckFileAbstract.h"
#include	"DynamicAbstract.h"

class	AIaAlgo;

namespace	botLoader
{
  class		Manager
  {
  public:
    Manager();
    ~Manager();

  public:
    typedef AIaAlgo								*(*instance_call)(void);

  public:
    void										initialize(std::string &);
    void										run();

  private:
    bool										addNewIa(const std::string &path);
	bool										updateIa(const std::string &path);

  public:
	  const AIaAlgo								*getSimpleBydos(void);
	  const AIaAlgo									*getBossBydos(void);
	  int										getSimpleBydosSize(void);
	  int										getBossBydosSize(void);

  public:
    static void									routine(Manager *);

  private:
    Manager(Manager const&);
    Manager& operator=(Manager const&);
  public:
	  typedef	std::map<std::string, AIaAlgo *>	bydos_type;

  private:
    ICheckFileAbstract							*_checkFile;
    DynamicAbstract								*_dynLoader;
    bydos_type									_simpleBydos;
    bydos_type									_bossBydos;
    std::map<std::string, UPDATE>				*_upList;
    Threads<void (*)(Manager *)>				_th;
    Thread::Mutex								_lock;
  };

}

#endif /* LOADER_MANAGER_H_ */
