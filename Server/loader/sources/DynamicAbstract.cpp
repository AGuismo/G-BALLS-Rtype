#include	"DynamicAbstract.h"

#ifdef WIN32

bool DynamicAbstract::DynamicOpen(const std::string &path)
{
	if ((handle = LoadLibrary(path.c_str())) == NULL)
		return false;
	return true;
}

void *DynamicAbstract::DynamicLoadSym(const std::string &symName)
{
	return (GetProcAddress(handle, symName.c_str()));
}

bool DynamicAbstract::DynamicClose(void)
{
	if (FreeLibrary(handle) == 0)
		return false;
	return true;
}

DynamicAbstract::DynamicAbstract()
{
	SetErrorMode(SEM_FAILCRITICALERRORS);
}

#elif	defined (linux)

bool DynamicAbstract::DynamicOpen(const std::string &path)
{
	if ((handle = dlopen(path.c_str(), RTLD_LAZY)) == NULL)
	  {
	    std::cerr << "Dynamic open: " << dlerror() << std::endl;
	    return false;
	  }
	return true;
}

void *DynamicAbstract::DynamicLoadSym(const std::string &symName)
{
  void	*sym = dlsym(handle, symName.c_str());

  if (sym == 0)
    std::cerr << "Dynamic loadSym: " << symName << ": " << dlerror() << std::endl;
  return (sym);
}

bool DynamicAbstract::DynamicClose(void)
{
	if (dlclose(handle) == 0)
		return false;
	return true;
}

DynamicAbstract::DynamicAbstract()
{
}

#else
	error "Unsupported operating system"
#endif // WIN32
