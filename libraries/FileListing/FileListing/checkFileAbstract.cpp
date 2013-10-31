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

	hFind = FindFirstFile(_fileToCheck.c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
		return NULL;

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
			std::cout << "FDFDFKLDFJDFDFGJDF" << std::endl;
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
// nothing for now
#else
error "Unsupported operating system"
#endif // WIN32