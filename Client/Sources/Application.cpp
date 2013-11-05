//
// Application.cpp for application in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 02:00:45 2013 brigno
// Last update Tue Nov  5 03:27:59 2013 brigno
//

#include	"Application.hh"
#include	"MenuWindow.hh"
#include	"Network.hh"

Application::Application()
{
}

Application::~Application()
{
}

void	Application::run(const std::string &ip, const std::string &port)
{
  Network	Network(ip, port);
  MenuWindow	Menu("R-Type", 1280, 720, &Network);

  Menu.run();
}
