#include	"DynamicAbstract.h"
#include	"myLibrary.h"

int				main()
{
  Fptr			dll;
  DynamicAbstract loader;

#if defined(WIN32)
  if (loader.DynamicOpen("myLibrary.dll") == false)
#elif defined(linux)
  if (loader.DynamicOpen("libmyLibrary.so") == false)
#endif
    {
      std::cerr << "FUCK  open" << std::endl;
#if defined(WIN32)
      system("pause");
#endif
      return (-1);
    }

  if ((dll = (Fptr)loader.DynamicLoadSym("getInstance")) == NULL)
    {
      std::cerr << "FUCK  load" << std::endl;
#if defined(WIN32)
      system("pause");
#endif
      return (-1);
    }

  CmyLibrary	*mlib;
  mlib = static_cast<CmyLibrary *>(dll());

  mlib->foo();
  loader.DynamicClose();

#if defined(WIN32)
  system("pause");
#endif
  return 0;
}
