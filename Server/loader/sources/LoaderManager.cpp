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
	_dynLoader = new DynamicAbstract;
	_upList = _checkFile->refreshFile();
	if (_upList == NULL)
		throw Exception("Bot library repertory empty or inexistant");

	for (std::map<std::string, UPDATE>::iterator it = _upList->begin(); it != _upList->end(); ++it)
	{
		std::cout << "[" << it->first.c_str() << "] [" << it->second << "]" << std::endl;
		if (it->second == NEW)
		{
			addNewIa("./botlibrary/" + it->first);
		}
		std::cout << std::endl;
	}
  }

  void	Manager::run()
  {
    _th.run();
    std::cout << "Loader manager started..." << std::endl;
  }

  bool	Manager::addNewIa(const std::string &path)
  {
	  if (_dynLoader->DynamicOpen(path) == true)
	  {
		  std::cout << "open working: " << path.c_str() << std::endl;
		  if (_dynLoader->DynamicLoadSym(std::string("getInstance")) != 0)
			std::cout << "loading working: " << path.c_str() << std::endl;
		  else
			  std::cout << "loading not working: " << path.c_str() << std::endl;
	  }
	  else
		  std::cout << "open not working: " << path.c_str() << std::endl;
	  return false;
  }

  void	Manager::routine(Manager *man)
  {
    while (true)
      {
		  sys::sleep(8);

		  man->_upList = man->_checkFile->refreshFile();
		  if (man->_upList != NULL)
		  {
		#ifdef DEBUG
			  for (std::map<std::string, UPDATE>::iterator it = man->_upList->begin(); it != man->_upList->end(); ++it)
			  {
				  std::cout << "[" << it->first.c_str() << "] [" << it->second << "]" << std::endl;
					  man->addNewIa("./botlibrary/" + it->first);
					  std::cout << "caca" << std::endl;
			  }
			  std::cout << std::endl;
		#endif
		  }
      }
  }
}


/*enum UPDATE
{
	NEW = 1,
	UPDATED,
	UNCHANGED,
	DELETED
};*/