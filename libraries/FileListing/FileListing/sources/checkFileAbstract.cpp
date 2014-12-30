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
  DIR								*dp;
  struct dirent							*dirp;
  struct stat 							st;
  std::string							nPath;
  std::map<std::string, time_t>::iterator				it;
  std::map<std::string, UPDATE>::iterator				ot;

  _update.clear();

#if defined(DEBUG)
  std::cout << _fileToCheck.c_str() << std::endl;
#endif
  if ((dp = opendir(_fileToCheck.c_str())) == NULL)
    return NULL;

  if ((dirp = readdir(dp)) == NULL)
    return NULL;

  do
  {
    nPath.clear();
    if (dirp->d_type == DT_REG)
    {
      nPath += _fileToCheck.c_str();
      nPath += "/";
      nPath += dirp->d_name;
      if (stat(nPath.c_str(), &st) == -1)
	return NULL;
      if ((it = _fileList.find(dirp->d_name)) == _fileList.end())
      {
	_fileList.insert(std::pair<std::string, time_t>(std::string(dirp->d_name), st.st_mtime));
	_update.insert(std::pair<std::string, UPDATE>(std::string(dirp->d_name), NEW));
      }
      else if (difftime(it->second, st.st_mtime) != 0)
      {
	it->second = st.st_mtime;
	_update.insert(std::pair<std::string, UPDATE>(std::string(dirp->d_name), UPDATED));
      }
      else
      {
	_update.insert(std::pair<std::string, UPDATE>(std::string(dirp->d_name), UNCHANGED));
      }
    }

  } while ((dirp = readdir(dp)) != NULL);


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

  closedir(dp);
  return &_update;
}

checkFileAbstract::checkFileAbstract(std::string &fileToCheck)
{
  _fileToCheck = fileToCheck;
}

#else
error "Unsupported operating system"
#endif // WIN32
