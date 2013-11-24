#include	<iostream>
#include	<cstring>
#include	<cstdlib>
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
			std::cerr << "Bot library repertory empty or inexistant but it's ok we have defaults IA ! Gniark Gniark !" << std::endl;
		else
		{
			for (std::map<std::string, UPDATE>::iterator it = _upList->begin(); it != _upList->end(); ++it)
			{
				//			std::cout << "[" << it->first.c_str() << "] [" << it->second << "]" << std::endl;
				if (it->second == NEW)
					addNewIa("./botlibrary/" + it->first);
				//			std::cout << std::endl;
			}
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
			sys::sleep(5);
			man->getBossBydos();
			man->getSimpleBydos();
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

	static int simpleRand(int a)
	{
		return rand()%(a);
	}

	AIaAlgo									*Manager::getBossBydos(void)
	{
		int									curLoop;
		int									goalLoop;
		bydos_type::iterator				it;

		if (_bossBydos.size() == 0)
			return NULL;
		curLoop = 0;
		goalLoop = simpleRand(_bossBydos.size());
	//	std::cout << "Size boss " << _bossBydos.size() << " result: " << goalLoop << std::endl;
		for (it = _bossBydos.begin(); it != _bossBydos.end(); ++it)
		{
			if (curLoop == goalLoop)
			{
//				std::cout << "ok => " << curLoop << std::endl;
			    return it->second->clone();
			}
			++curLoop;
		}
		return NULL;
	}

	AIaAlgo									*Manager::getSimpleBydos(void)
	{
		int									curLoop;
		int									goalLoop;
		bydos_type::iterator				it;

		if (_simpleBydos.size() == 0)
			return NULL;
		curLoop = 0;
		goalLoop = simpleRand(_simpleBydos.size());
//		std::cout << "Size boss " << _simpleBydos.size() << " result: " << goalLoop << std::endl;
		for (it = _simpleBydos.begin(); it != _simpleBydos.end(); ++it)
		{
			if (curLoop == goalLoop)
			{
				//				std::cout << "ok => " << curLoop << std::endl;
			    return it->second->clone();
			}
			++curLoop;
		}
		return NULL;
	}

	int										Manager::getBossBydosSize(void)
	{
		return  (_bossBydos.size());
	}

	int										Manager::getSimpleBydosSize(void)
	{
		return  (_bossBydos.size());
	}

Manager	&Manager::getInstance()
{
    static Manager manager;
    return manager;
}

}
