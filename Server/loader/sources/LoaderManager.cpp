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
//		std::cout << "Bot loading file: " << dName.c_str() << std::endl;
		_checkFile = new checkFileAbstract(dName);
		_dynLoader = new DynamicAbstract;
		_upList = _checkFile->refreshFile();
		if (_upList == NULL)
			throw Exception("Bot library repertory empty or inexistant");

		for (std::map<std::string, UPDATE>::iterator it = _upList->begin(); it != _upList->end(); ++it)
		{
//			std::cout << "[" << it->first.c_str() << "] [" << it->second << "]" << std::endl;
			if (it->second == NEW)
				addNewIa("./botlibrary/" + it->first);
//			std::cout << std::endl;
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
			if (inst != 0)
			{
				AIaAlgo	*ia = inst();

				if (ia->isIa())
				{
//					std::cout << "ok ia" << std::endl;
					_simpleBydos.insert(std::pair<std::string, AIaAlgo *>(path, ia));
				}
				else
				{
//					std::cout << "ok boss" << std::endl;
					_bossBydos.insert(std::pair<std::string, AIaAlgo *>(path, ia));
				}
				return true;
			}
/*			else
				std::cout << "open not working: " << path.c_str() << std::endl;*/
		}
		return false;
	}

	bool	Manager::updateIa(const std::string &path)
	{
		if (_dynLoader->DynamicOpen(path) == true)
		{
			instance_call	inst;

			inst = (instance_call)_dynLoader->DynamicLoadSym(std::string("getInstance"));
			if (inst != 0)
			{
				AIaAlgo	*ia = inst();

				if (ia->isIa())
				{
//					std::cout << "ok ia" << std::endl;
					_simpleBydos[path] = ia;
				}
				else
				{
//					std::cout << "ok boss" << std::endl;
					_bossBydos[path] = ia;
				}
				return true;
			}
/*			else
				std::cout << "open not working: " << path.c_str() << std::endl;*/
		}
		return false;
	}

	void	Manager::routine(Manager *man)
	{
		  (void)man;
		  while (true)
		  {
			  sys::sleep(10);
			  man->_upList = man->_checkFile->refreshFile();
			  if (man->_upList != NULL)
				  {
					  for (std::map<std::string, UPDATE>::iterator it = man->_upList->begin(); it != man->_upList->end(); ++it)
					  {
	//					  std::cout << "[" << it->first.c_str() << "] [" << it->second << "]" << std::endl;
						  if (it->second == NEW)
						  {
//							  std::cout << "new IA" << it->first.c_str() << std::endl;
							  man->addNewIa("./botlibrary/" + it->first);
						  }
						  else if (it->second == UPDATED)
						  {
//							 std::cout << "Update: " << it->first.c_str() << std::endl;
							 man->addNewIa("./botlibrary/" + it->first);
						  }
					  }
//					  std::cout << std::endl;
				  }
			}
	}
}

/*AIaAlgo									*Manager::getSimpleBydos(void)
{
	return NULL;
}*/




/*AIaAlgo									*Manager::getSimpleBydos(void)
{

}

AIaAlgo									*Manager::getBossBydos(void)
{

}*/