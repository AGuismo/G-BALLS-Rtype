//
// Application.cpp for application in /home/brigno/GIT/G-BALLS-Rtype/Client
//
// Made by brigno
// Login   <brigno@epitech.net>
//
// Started on  Tue Nov  5 02:00:45 2013 brigno
// Last update Sat Nov 23 18:01:04 2013 brigno
//

#include	"Application.hh"
#include	"AScreen.hh"
#include	"MenuWindow.hh"
#include	"GameWindow.hh"
#include	"NetworkManager.hh"

const char	*Application::WINDOW_NAME = "R-Type";

Application::Application()
{
	_listScreen.push_back(new MenuWindow(_window));
	_listScreen.push_back(new GameWindow(_window));
}

Application::~Application()
{
  for (screen_list::iterator it = _listScreen.begin(); it != _listScreen.end(); ++it)
    delete *it;
}

bool	Application::initialize()
{
  this->_window.create(sf::VideoMode(WIDTH, HEIGHT), WINDOW_NAME,
		       sf::Style::Titlebar | sf::Style::Close);
  this->_window.setVerticalSyncEnabled(true);
  this->_window.setFramerateLimit(25);
  try
    {
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
  return (true);
}

void	Application::run()
{
  int	screenIdx = AScreen::SCR_MENU;

  network::Manager::getInstance().run();
  while (this->_window.isOpen())
    {
      screenIdx = _listScreen[screenIdx]->run();
    }
}
