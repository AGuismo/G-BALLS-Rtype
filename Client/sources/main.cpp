//
// main.cpp for main in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 12:59:21 2013 brigno
// Last update Fri Nov 22 14:00:22 2013 lambert kevin
//

#include	"Application.hh"
#include	"types.hh"

#if defined(WIN32)
template class __declspec(dllexport) std::vector<Ruint8>;
#endif

int	main()
{
  Application	application;

  if (!application.initialize())
    return (1);
  application.run();
  return (0);
}
