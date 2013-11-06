//
// main.cpp for main in /home/brigno/Projects/R-Type/r-type/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Wed Oct 23 12:59:21 2013 brigno
// Last update Tue Nov  5 13:41:41 2013 brigno
//

#include	"Application.hh"

int	main(int ac, char **av)
{
  Application	application;

  if (ac == 3)
    application.run(std::string(av[1]), std::string(av[2]));
  else
    std::cout << "USAGE : ./Client AdresseIp Port" << std::endl;
  return 0;
}
