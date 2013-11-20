//
// Application.cpp for application in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 02:00:45 2013 brigno
// Last update Wed Nov 20 23:06:38 2013 brigno
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

void	Application::run()
{
  Network	Network("127.0.0.1", "4242");
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
