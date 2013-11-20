//
// Application.cpp for application in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 02:00:45 2013 brigno
// Last update Wed Nov 13 10:10:44 2013 brigno
//

#include	"Application.hh"
#include	"AScreen.hh"
#include	"Network.hh"
#include	"MenuWindow.hh"

Application::Application()
{
}

Application::~Application()
{
}

void	Application::run(const std::string &ip, const std::string &port)
{
  Network	Network(ip, port);
  MenuWindow	*Menu;

  try
    {
      Menu = new MenuWindow("R-Type Connection", 1280, 720, &Network);
      Menu->run();
    }
  catch (AScreen::Exception &e)
    {
      std::cerr <<  e.what() << std::endl;
      return;
    }
}
