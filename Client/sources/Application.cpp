//
// Application.cpp for application in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 02:00:45 2013 brigno
// Last update Thu Nov 21 15:16:44 2013 lambert kevin
//

#include	"Application.hh"
#include	"AScreen.hh"
#include	"Network.hh"
#include	"MenuWindow.hh"
#include	"gameWindow.h"

const char	*Application::WINDOW_NAME = "R-Type";

Application::Application()
{
  _listScreen.push_back(new MenuWindow(_window, _network));
  _listScreen.push_back(new GameWindow(_window, _network));
}

Application::~Application()
{

}

bool	Application::initialize()
{
  this->_window.create(sf::VideoMode(WIDTH, HEIGHT), WINDOW_NAME,
		       sf::Style::Titlebar | sf::Style::Close);
  this->_window.setVerticalSyncEnabled(true);
  this->_window.setFramerateLimit(25);
  try
    {
      // _network.initialize();
      for (screen_list::iterator it = _listScreen.begin(); it != _listScreen.end(); ++it)
	{
	  (*it)->load();
	}
    }
  catch (const AScreen::Exception &e)
    {
      std::cerr <<  e.what() << std::endl;
      return (false);
    }
  // catch (const Network::Exception &e)
  //   {
  //     std::cerr <<  e.what() << std::endl;
  //     return (false);
  //   }
  return (true);
}

void	Application::run()
{
  int	screenIdx = AScreen::SCR_MENU;

  // _network.run();
  while (this->_window.isOpen())
    {
      screenIdx = _listScreen[screenIdx]->run();
    }
}
