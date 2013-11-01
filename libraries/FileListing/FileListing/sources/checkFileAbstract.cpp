#include	"checkFileAbstract.h"


#ifdef WIN32


std::map<std::string, UPDATE>						*checkFileAbstract::refreshFile(void)
{
	WIN32_FIND_DATA									ffd;
	HANDLE											hFind = INVALID_HANDLE_VALUE;
	std::map<std::string, FILETIME>::iterator		it;
	std::map<std::string, UPDATE>::iterator			ot;

	_update.clear();

	if (_fileToCheck.size() > (MAX_PATH))
		return NULL;
	std::cout << _fileToCheck.c_str() << std::endl;
	hFind = FindFirstFile(_fileToCheck.c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		std::cerr << "caca là" << std::endl;
		return NULL;
	}

	do 
	{
		if (ffd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
		{
			if ((it = _fileList.find(ffd.cFileName)) == _fileList.end())
			{
				_fileList.insert(std::pair<std::string, FILETIME>(std::string(ffd.cFileName), ffd.ftLastWriteTime));
				_update.insert(std::pair<std::string, UPDATE>(std::string(ffd.cFileName), NEW));
			}
			else if (CompareFileTime(&(it->second), &ffd.ftLastWriteTime) != 0)
			{
				it->second = ffd.ftLastWriteTime;
				_update.insert(std::pair<std::string, UPDATE>(std::string(ffd.cFileName), UPDATED));
			}
			else
			{
				_update.insert(std::pair<std::string, UPDATE>(std::string(ffd.cFileName), UNCHANGED));
			}
		}
	} while (FindNextFile(hFind, &ffd) != 0);


	for (it = _fileList.begin(); it != _fileList.end(); ++it)
	{
		ot = _update.find(it->first);
		if (ot == _update.end())
		{
			_update.insert(std::pair<std::string, UPDATE>(std::string(it->first.c_str()), DELETED));
			_fileList.erase(it);
			it = _fileList.begin();
		}
	}

	FindClose(hFind);
	return &_update;
}

checkFileAbstract::checkFileAbstract(std::string &fileToCheck)
{
	_fileToCheck = fileToCheck;
	_fileToCheck += "\\*";
}



#elif	defined (linux)


std::map<std::string, UPDATE>						*checkFileAbstract::refreshFile(void)
{
	DIR												*dp;
	struct dirent									*dirp;
	std::map<std::string, time_t>::iterator			it;
	std::map<std::string, UPDATE>::iterator			ot;

	_update.clear();


	std::cout << _fileToCheck.c_str() << std::endl;

	if ((dp = opendir(_fileToCheck.c_str())) == NULL)
	{
		std::cerr << "open dir failed" << std::endl;
		return NULL;
	}

	while ((dirp = readdir(dp)) != NULL)
	{
		std::cout << dirp->d_name << std::endl;
	}



	/*	do
	{
	if (ffd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY)
	{
	if ((it = _fileList.find(ffd.cFileName)) == _fileList.end())
	{
	_fileList.insert(std::pair<std::string, FILETIME>(std::string(ffd.cFileName), ffd.ftLastWriteTime));
	_update.insert(std::pair<std::string, UPDATE>(std::string(ffd.cFileName), NEW));
	}
	else if (CompareFileTime(&(it->second), &ffd.ftLastWriteTime) != 0)
	{
	it->second = ffd.ftLastWriteTime;
	_update.insert(std::pair<std::string, UPDATE>(std::string(ffd.cFileName), UPDATED));
	}
	else
	{
	_update.insert(std::pair<std::string, UPDATE>(std::string(ffd.cFileName), UNCHANGED));
	}
	}
	} while (FindNextFile(hFind, &ffd) != 0);


	for (it = _fileList.begin(); it != _fileList.end(); ++it)
	{
	ot = _update.find(it->first);
	if (ot == _update.end())
	{
	_update.insert(std::pair<std::string, UPDATE>(std::string(it->first.c_str()), DELETED));
	_fileList.erase(it);
	it = _fileList.begin();
	}
	}*/

	closedir(dp);
	return &_update;
}

checkFileAbstract::checkFileAbstract(std::string &fileToCheck)
{
	_fileToCheck = fileToCheck;
	//_fileToCheck += "\\*";
}

#else
error "Unsupported operating system"
#endif // WIN32