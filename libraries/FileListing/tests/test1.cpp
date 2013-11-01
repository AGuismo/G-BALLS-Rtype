#include	"checkFileAbstract.h"

int						main(int ac, char *av[])
{
  int					i = 0;
  ACheckFileAbstract		*listing;
  std::string			dName("../FileListing/AU BON C");
  std::map<std::string, UPDATE>	*list;

  listing = new checkFileAbstract(dName);

  std::cout << av[1] << std::endl;

  while (i < 10)
    {
      list = listing->refreshFile();
	  if (list == NULL)
	  {
		  std::cerr << "repertory inexistant" << std::endl;
#if defined(WIN32)
		  system("pause");
#endif
		  break;
	  }
      for (std::map<std::string, UPDATE>::iterator it = list->begin(); it != list->end(); ++it)
	std::cout << "[" << it->first.c_str() << "] [" << it->second << "]" << std::endl;
#if defined(WIN32)
      system("pause");
#endif
      ++i;
    }
  return 1;
}
