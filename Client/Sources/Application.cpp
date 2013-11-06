//
// Application.cpp for application in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 02:00:45 2013 brigno
// Last update Wed Nov  6 02:18:36 2013 brigno
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
  int		screenIndex = 0;
  MenuWindow	*Menu;

  try
    {
      Menu = new MenuWindow("R-Type", 1280, 720, &Network);
    }
  catch (AScreen::Exception &e)
    {
      std::cerr <<  e.what() << std::endl;
      return ;
    }
  this->addScreen(Menu);
  while (screenIndex >= 0)
    {
      screenIndex = this->_listScreen[screenIndex]->run();
    }
}

void	Application::addScreen(AScreen *screen)
{
  this->_listScreen.push_back(screen);
}
