#include	<algorithm>
#include	<iostream>
#include	"Application.hh"
#include	"GameException.hh"
#include	"MenuException.hh"
#include	"MenuGame.hh"
#include	"LoaderException.hh"
#include	"Database.hh"
#include	"Salt.hpp"
#include	"Game.h"
#include	"Callback.hh"
#include	"Client.hh"

Salt::size_type	Salt::SALT = 42;

Application::Application():
  _menuManager(this, _menuOutput, _input), _gameManager(this, _gameOutput, _input)
{
  std::string	file("botlibrary");

  if (!Database::getInstance().loadFile(rtype::Env::getInstance().database.DatabasePath))
    std::cout << "Warning: There is no Database or a corrupt Database in "
	      << rtype::Env::getInstance().database.DatabasePath << std::endl
  	      << "Client Database will be created for further usage" << std::endl;
  Database::getInstance().newClient("root", md5("4242"), database::SUPER_USER, true);
  try
    {
      _menuManager.initialize(); // Load the menu
      _gameManager.initialize(); // Load the game system
      botLoader::Manager::getInstance().initialize(file); // Load the bot-Loader
    }
  catch (const menu::Exception &e) // Menu loader exception
    {
      std::cerr << "In Application::run(), catch: " << e.what() << std::endl;
      throw Application::InitExcept("Application Init fail");
    }
  catch (const game::Exception &e) // game loader exception
    {
      std::cerr << "In Application::run(), catch: " << e.what() << std::endl;
      throw Application::InitExcept("Application Init fail");
    }
  catch (const botLoader::Exception &e) // Catch Bot loader exception
    {
      std::cerr << "In Application::run(), catch: " << e.what() << std::endl;
      throw Application::InitExcept("Application Init fail");
    }
  Database::getInstance().saveFile(rtype::Env::getInstance().database.DatabasePath);
}

Application::~Application()
{
  Database::getInstance().saveFile(rtype::Env::getInstance().database.DatabasePath);
}

void	Application::run()
{
  std::cout << "Start Application::Run" << std::endl;
  _gameManager.run();
  botLoader::Manager::getInstance().run();
  _menuManager.run();
  _active = true;
  routine();
}

void	Application::updateClients()
{
  client_list::iterator it;

  for (it = _clients.begin(); it != _clients.end();)
    {
      (*it)->update();
      if (!(*it)->isUse())
	{
	  std::cout << "Application::updateClients(): " << "Client deleted" << std::endl;
	  delete *it;
	  it = _clients.erase(it);
	}
      else
	++it;
    }
}

void	Application::stop(menu::Client *client)
{
  (void)client;
  _active = false;
}

void	Application::routine()
{
  while (_active)
    {
      ICallbacks	*callbacks = _input.pop();

      (*callbacks)();
      delete callbacks;
      updateClients();
    }
  _gameManager.stop();
  _menuManager.stop();
  botLoader::Manager::getInstance().stop();
}

void	Application::ClientLeaveGame(game::Client *client)
{
  client_list::iterator	appIt;

#if defined(DEBUG)
  std::cout << "Application::ClientLeaveGame(): " << "Player Leave Game..." << std::endl;
#endif
  appIt = std::find_if(_clients.begin(), _clients.end(), PredicateGameClient(client));
  (*appIt)->menu().inUse(true);
  (*appIt)->game().inUse(false);
}

void	Application::newClient(Client *client)
{
#if defined(DEBUG)
  std::cout << "Application::newClient(): " << "new Client" << std::endl;
#endif
  _clients.push_back(client);
}

void	Application::newGame(menu::Game *game)
{
  menu::Game::client_list::iterator	menuIt = game->getClients().begin();
  Game::client_list			clients;

#if defined(DEBUG)
  std::cout << "Application::newGame(): " << "Start Game..." << std::endl;
#endif
  for (; menuIt != game->clients().end(); ++menuIt)
    {
      client_list::iterator	appIt;

      appIt = std::find_if(_clients.begin(), _clients.end(), PredicateMenuClient(*menuIt));
      (*appIt)->game().inUse(true);
      (*appIt)->game().hasLeft(false);
      (*appIt)->game().alive(true);
      (*appIt)->menu().inUse(false);
      clients.push_back(&(*appIt)->game());
    }
  _games.push_back(game);
  game->game(new Game(clients));
  _gameOutput.push(new Callback<game::Manager, Game>(&_gameManager, game->game(),
						     &game::Manager::newGame));
}

void	Application::endGame(Game *game)
{
  Game::client_list::iterator	gameIt = game->clients().begin();
  game_list::iterator		thatGame;

#if defined(DEBUG)
  std::cout << "Application::endGame(): " << "End of Game..." << std::endl;
#endif
  for (; gameIt != game->clients().end(); ++gameIt)
    {
      client_list::iterator	appIt;

      appIt = std::find_if(_clients.begin(), _clients.end(), PredicateGameClient(*gameIt));
      (*appIt)->game().inUse(true);
      (*appIt)->menu().inUse(false);
    }
  thatGame = std::find_if(_games.begin(), _games.end(), PredicateGame(game));
  if (thatGame == _games.end())
    return;
  _menuOutput.push(new Callback<menu::Manager, menu::Game>(&_menuManager, *thatGame,
							   &menu::Manager::endGame));
  _games.erase(thatGame);
  delete game;
}

///////////////////////
//  Exception Class  //
///////////////////////
Application::InitExcept::InitExcept(const std::string &msg) throw() :
  _what(msg)
{

}

Application::InitExcept::InitExcept (const Application::InitExcept &src) throw() :
  _what(src._what)
{

}

Application::InitExcept::~InitExcept() throw()
{

}

Application::InitExcept& Application::InitExcept::operator=(Application::InitExcept const &src) throw()
{
  if (&src != this)
    {
      _what = src._what;
    }
  return (*this);
}

const char	*Application::InitExcept::what() const throw()
{
  return (_what.c_str());
}

/////////////////////////////
//  Application Predicate  //
/////////////////////////////

Application::PredicateMenuClient::PredicateMenuClient(menu::Client *client):
  _client(client)
{

}

bool	Application::PredicateMenuClient::operator()(const Client *src)
{
  return (&src->menu() == _client);
}

Application::PredicateGameClient::PredicateGameClient(game::Client *client):
  _client(client)
{

}

bool	Application::PredicateGameClient::operator()(const Client *src)
{
  return (&src->game() == _client);
}

Application::PredicateGame::PredicateGame(Game *game) :
  _game(game)
{

}

bool	Application::PredicateGame::operator()(const menu::Game *src)
{
  return (src->game() == _game);
}
