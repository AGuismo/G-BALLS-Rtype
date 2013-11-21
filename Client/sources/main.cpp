//
// main.cpp for main in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 12:59:21 2013 brigno
// Last update Thu Nov 21 19:33:25 2013 lambert kevin
//

#include	"Application.hh"

int	main()
{
  Application	application;

  if (!application.initialize())
    return (1);
  application.run();
  return (0);
}
