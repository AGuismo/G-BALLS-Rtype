#include	<iostream>
#include	<cstring>
#include	"sys.hh"
#include	"Bind.hpp"
#include	"LoaderManager.hh"
#include	"LoaderException.hh"

namespace	botLoader
{
  Manager::Manager():
    _th(Func::Bind(&Manager::routine, this))
  {

  }

  Manager::~Manager()
  {
    _th.cancel();
  }

  void	Manager::initialize(std::string &dName)
  {
	#ifdef DEBUG
	std::cout << "Bot loading file: " << dName.c_str() << std::endl;
	#endif
	_checkFile = new checkFileAbstract(dName);
	_upList = _checkFile->refreshFile();
	if (_upList == NULL)
		throw Exception("Bot library repertory empty or inexistant");
	#ifdef DEBUG	
	for (std::map<std::string, UPDATE>::iterator it = _upList->begin(); it != _upList->end(); ++it)
		std::cout << "[" << it->first.c_str() << "] [" << it->second << "]" << std::endl;
	#endif
  }

  void	Manager::run()
  {
    _th.run();
    std::cout << "Loader manager started..." << std::endl;
  }

  void	Manager::routine(Manager *thisPtr)
  {
    (void)thisPtr;
    while (true)
      {
	sys::sleep(1);
      }
  }
}
