#include	<iostream>
#include	<cstring>
#include	"sys.hh"
#include	"Bind.hpp"
#include	"IaAlgo.hh"
#include	"LoaderManager.hh"
#include	"LoaderException.hh"

namespace	botLoader
{
	Manager::Manager() :
		_th(Func::Bind(&Manager::routine, this))
	{

	}

	Manager::~Manager()
	{
		_th.cancel();
	}

	void	Manager::initialize(std::string &dName)
	{
		std::cout << "Bot loading file: " << dName.c_str() << std::endl;
		_checkFile = new checkFileAbstract(dName);
		_dynLoader = new DynamicAbstract;
		_upList = _checkFile->refreshFile();
		if (_upList == NULL)
			throw Exception("Bot library repertory empty or inexistant");

		for (std::map<std::string, UPDATE>::iterator it = _upList->begin(); it != _upList->end(); ++it)
		{
			std::cout << "[" << it->first.c_str() << "] [" << it->second << "]" << std::endl;
			if (it->second == NEW)
				addNewIa("./botlibrary/" + it->first);
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
			instance_call	inst;

			inst = (instance_call)_dynLoader->DynamicLoadSym(std::string("getInstance"));
			if (inst != NULL)
			{
				AIaAlgo	*ia = inst();

				if (ia->isIa())
				{
					std::cout << "ok" << std::endl;
					_simpleBydos[path] = ia;
				}
				else
					_bossBydos[path] = ia;

			}
			else
				std::cout << "open not working: " << path.c_str() << std::endl;
		}
		return false;
	}

	void	Manager::routine(Manager *man)
	{
	  (void)man;
<<<<<<< HEAD
		/*    while (true)
=======
	  /*
		    while (true)
>>>>>>> eefc8a5a23d29d44442974b2c223faba8d879571
			  {
			  sys::sleep(8);

			  man->_upList = man->_checkFile->refreshFile();
			  if (man->_upList != NULL)
			  {
			  #ifdef DEBUG
			  for (std::map<std::string, UPDATE>::iterator it = man->_upList->begin(); it != man->_upList->end(); ++it)
			  {
			  std::cout << "[" << it->first.c_str() << "] [" << it->second << "]" << std::endl;
			  //man->addNewIa("./botlibrary/" + it->first);
			  }
			  std::cout << std::endl;
			  #endif
			  }
			  }*/
	}

}
/*enum UPDATE
  {
  NEW = 1,
  UPDATED,
  UNCHANGED,
  DELETED
  };*/
