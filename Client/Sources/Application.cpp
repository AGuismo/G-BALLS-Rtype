//
// Application.cpp for application in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 02:00:45 2013 brigno
// Last update Wed Nov  6 04:00:09 2013 brigno
//

#include	"Application.hh"
#include	"AScreen.hh"
#include	"Network.hh"
#include	"MenuWindow.hh"
#include	"LobbyWindow.hh"

Application::Application()
{
}

Application::~Application()
{
}

bool	Application::createWindows(Network *network, int screenIndex)
{
  MenuWindow	*Menu;
  LobbyWindow	*Lobby;

  try
    {
      switch (screenIndex)
	{
	case 0:
	  Menu = new MenuWindow("R-Type Connection", 1280, 720, network);
	  this->addScreen(Menu);
	  break;
	case 1:
	  Lobby = new LobbyWindow("R-Type Menu", 1280, 720, network);
	  this->addScreen(Lobby);
	  break;
	}
    }
  catch (AScreen::Exception &e)
    {
      std::cerr <<  e.what() << std::endl;
      return false;
    }
  return true;
}

bool	Application::initApp(Network *network)
{
  MenuWindow	*Menu;

  try
    {
      Menu = new MenuWindow("R-Type Connection", 1280, 720, network);
    }
  catch (AScreen::Exception &e)
    {
      std::cerr <<  e.what() << std::endl;
      return false;
    }
  this->addScreen(Menu);
  return true;
}

void	Application::run(const std::string &ip, const std::string &port)
{
  Network	Network(ip, port);
  int		screenIndex = 0;

  if (this->initApp(&Network) == false)
    return ;
  while (screenIndex >= 0)
    {
      screenIndex = this->_listScreen[screenIndex]->run();
      std::cout << screenIndex << std::endl;
      if (this->createWindows(&Network, screenIndex) == false)
	return ;
    }
}

void	Application::addScreen(AScreen *screen)
{
  this->_listScreen.push_back(screen);
}
