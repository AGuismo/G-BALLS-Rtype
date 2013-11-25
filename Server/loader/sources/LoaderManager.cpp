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
	  Thread::MutexGuard	guard(_lock);
		_checkFile = new checkFileAbstract(dName);
		_dynLoader = new DynamicAbstract;
		_upList = _checkFile->refreshFile();
		if (_upList == NULL)
			std::cerr << "Bot library repertory empty or inexistant but it's ok we have defaults IA ! Gniark Gniark !" << std::endl;
		else
		{
			for (std::map<std::string, UPDATE>::iterator it = _upList->begin(); it != _upList->end(); ++it)
			{
				if (it->second == NEW)
					addNewIa("./botlibrary/" + it->first);
			}
		}
	}

	void	Manager::run()
	{
	  _active = true;
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
					_simpleBydos.insert(std::pair<std::string, AIaAlgo *>(path, ia));
				}
				else
				{
					_bossBydos.insert(std::pair<std::string, AIaAlgo *>(path, ia));
				}
				_dynLoader->DynamicClose();
				return true;
			}
			_dynLoader->DynamicClose();
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
					_simpleBydos[path] = ia;
				}
				else
				{
					_bossBydos[path] = ia;
				}
				_dynLoader->DynamicClose();
				return true;
			}
			_dynLoader->DynamicClose();
		}
		return false;
	}

  void	Manager::stop()
  {
    _active = false;
  }

	void	Manager::routine(Manager *man)
	{
		(void)man;
		while (man->_active)
		{
			sys::sleep(5);
			man->_lock.lock();
			man->_upList = man->_checkFile->refreshFile();
			if (man->_upList != NULL)
			{
				for (std::map<std::string, UPDATE>::iterator it = man->_upList->begin(); it != man->_upList->end(); ++it)
				{
					if (it->second == NEW)
					{
						man->addNewIa("./botlibrary/" + it->first);
					}
					else if (it->second == UPDATED)
					{
						man->addNewIa("./botlibrary/" + it->first);
					}
				}
			}
			man->_lock.unlock();
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
		Thread::MutexGuard				guard(_lock);

		if (_bossBydos.size() == 0)
			return NULL;
		curLoop = 0;
		goalLoop = simpleRand(_bossBydos.size()) - 1;
		for (it = _bossBydos.begin(); it != _bossBydos.end(); ++it)
		{
			if (curLoop == goalLoop)
			{
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
		Thread::MutexGuard				guard(_lock);

		if (_simpleBydos.size() == 0)
			return NULL;
		curLoop = 0;
		goalLoop = simpleRand(_simpleBydos.size()) - 1;
		for (it = _simpleBydos.begin(); it != _simpleBydos.end(); ++it)
		{
			if (curLoop == goalLoop)
			{
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
