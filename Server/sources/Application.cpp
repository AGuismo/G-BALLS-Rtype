#include	<algorithm>
#include	<iostream>
#include	"Application.hh"
#include	"GameManager.hh"
#include	"MenuManager.hh"
#include	"GameException.hh"
#include	"MenuException.hh"
#include	"MenuGame.hh"
#include	"LoaderException.hh"
#include	"Database.hh"
#include	"Salt.hpp"
#include	"Game.hh"
#include	"Callback.hh"
#include	"Client.hh"

Salt::size_type	Salt::SALT = 42;
loglib::Log	Application::log;

Application::Application():
  _menuManager(0), _gameManager(0),
  _log(rtype::Env::LOG_FILE.c_str(), std::ofstream::app | std::ofstream::out)
{
  std::string	file("botlibrary");

  if (!_log)
  {
    log << "Unable to start loggin on " << rtype::Env::LOG_FILE.c_str()
	<< ". Switching to standard output." << std::endl;
  }
  else
    Application::log.changeStream(_log);
  log << "rtype server: Initialize..." << std::endl;
  if (!Database::getInstance().loadFile(rtype::Env::getInstance().database.DatabasePath))
#if defined(DEBUG)
    log << "Warning: There is no Database or a corrupt Database in "
	<< rtype::Env::getInstance().database.DatabasePath
	<< ". Client Database will be created for further usage" << std::endl;
#endif
  Database::getInstance().newClient("root", md5("4242"), database::SUPER_USER, true);
  try
  {
    _menuManager = new menu::Manager(_menuOutput, _input);
    _menuManager->initialize(); // Load the menu
    _gameManager = new game::Manager(_gameOutput, _input);
    _gameManager->initialize(); // Load the game system
    botLoader::Manager::getInstance().initialize(file); // Load the bot-Loader
  }
  catch (const menu::Exception &e) // Menu loader exception
  {
    log << "In Application::run(), catch: " << e.what() << std::endl;
    delete _menuManager;
    throw Application::InitExcept("Application Init fail");
  }
  catch (const game::Exception &e) // game loader exception
  {
    log << "In Application::run(), catch: " << e.what() << std::endl;
    delete _menuManager;
    delete _gameManager;
    throw Application::InitExcept("Application Init fail");
  }
  catch (const botLoader::Exception &e) // Catch Bot loader exception
  {
    log << "In Application::run(), catch: " << e.what() << std::endl;
    delete _menuManager;
    delete _gameManager;
    throw Application::InitExcept("Application Init fail");
  }
  Database::getInstance().saveFile(rtype::Env::getInstance().database.DatabasePath);
  log << "rtype server: Initialization success" << std::endl;
}

Application::~Application()
{
  Database::getInstance().saveFile(rtype::Env::getInstance().database.DatabasePath);
  delete _menuManager;
  delete _gameManager;
  for (client_list::iterator it = _clients.begin(); it != _clients.end(); ++it)
    delete *it;
  log << "rtype server: deleted" << std::endl;
}

void	Application::run()
{
#if defined(DEBUG)
  log << "Start Application::Run" << std::endl;
#endif
  _gameManager->run();
  botLoader::Manager::getInstance().run();
  _menuManager->run();
  _active = true;
  log << "rtype server: started" << std::endl;
  routine();
}

// void	Application::updateClients()
// {
//   client_list::iterator it;

//   for (it = _clients.begin(); it != _clients.end();)
//     {
//       if ((*it)->state() == State::DELETED || (*it)->state() == State::DISCONNECTED)
// 	{
// #if defined(DEBUG)
// 	  std::cout << "Application::updateClients(): " << "Client deleted";
// #endif
// 	  delete *it;
// 	  it = _clients.erase(it);
// 	}
//       else
// 	++it;
//     }
// }

void	Application::stop(menu::Client *client)
{
  (void)client;
  _active = false;
}

void	Application::routine()
{
  while (_active)
  {
    IApplicationCallbacks	*callbacks = _input.pop();

    (*callbacks)(this);
    delete callbacks;
    // updateClients();
  }
  _gameManager->stop();
  _menuManager->stop();
  botLoader::Manager::getInstance().stop();
  log << "rtype server: stopped" << std::endl;
}

void	Application::clientDisconnected(requestCode::SessionID clientID)
{
  client_list::iterator	appIt;

#if defined(DEBUG)
  log << "Application::ClientDisconnected(): " << "Client in menu is disconnected" << std::endl;
#endif
  appIt = std::find_if(_clients.begin(), _clients.end(), PredicateClient(clientID));
  (*appIt)->state(Client::DISCONNECTED); // erase/delete appIt ? Memory Leak
  // _menuOutput.push(new Callback<menu::Manager, requestCode::SessionID>(_menuManager, (*appIt)->id(),
  // 								       &menu::Manager::clientLeaveGame));
}


void	Application::ClientLeaveGame(requestCode::SessionID client)
{
  client_list::iterator	appIt;

#if defined(DEBUG)
  log << "Application::ClientLeaveGame(): " << "Player Leave Game..." << std::endl;
#endif
  appIt = std::find_if(_clients.begin(), _clients.end(), PredicateClient(client));
  (*appIt)->state(Client::MENU);
  _menuOutput.push(new Callback<menu::Manager, requestCode::SessionID>(_menuManager, (*appIt)->id(),
								       &menu::Manager::clientLeaveGame));
  // (*appIt)->menu()->inUse(true);
  // delete (*appIt)->game();
  // (*appIt)->game(0);
  //  (*appIt)->game().hasLeft(false);
  //  (*appIt)->game().alive(true);
}

void	Application::newClient(requestCode::SessionID clientID)
{
#if defined(DEBUG)
  log << "Application::newClient(): " << "new Client with ID(" << clientID << ")" << std::endl;
#endif
  _clients.push_back(new Client(clientID, Client::MENU));
}

void	Application::newGame(menu::Game *menuGame)
{
  menu::Game::client_list::iterator	menuIt = menuGame->getClients().begin();
  game::Game::client_list		clients;
  game::Game				*loadedGame;

#if defined(DEBUG)
  log << "Application::newGame(): " << "Start Game..." << std::endl;
#endif
  for (; menuIt != menuGame->clients().end(); ++menuIt)
  {
    client_list::iterator	appIt;
    game::Client		*gameClient;

    appIt = std::find_if(_clients.begin(), _clients.end(), PredicateClient((*menuIt)->sessionID()));
    gameClient = new game::Client((*appIt)->id());
    // (*appIt)->game(gameClient);
    // gameClient->inUse(true);
    // (*appIt)->menu()->inUse(false);
    (*appIt)->state(Client::GAME);
    clients.push_back(gameClient);
  }
  loadedGame = new game::Game(clients);
  _games.push_back(game_pair(menuGame, loadedGame));
  // menuGame->game(loadedGame);
  _gameOutput.push(new Callback<game::Manager, game::Game *>(_gameManager, loadedGame,
							     &game::Manager::newGame));
}

void	Application::endGame(const game::Game *loadedGame)
{
  game::Game::client_list::const_iterator	gameIt;
  game_list::iterator				thatGame;

  thatGame = std::find_if(_games.begin(), _games.end(), PredicateGame(loadedGame));
  if (thatGame == _games.end())
    return;
#if defined(DEBUG)
  log << "Application::endGame(): " << thatGame->second << " End of Game..." << std::endl;
#endif
  for (gameIt = thatGame->second->clients().begin();
       gameIt != thatGame->second->clients().end(); ++gameIt)
  {
    client_list::iterator	appIt;

    appIt = std::find_if(_clients.begin(), _clients.end(), PredicateClient((*gameIt)->clientID()));
    // (*appIt)->game().inUse(true);
    // (*appIt)->menu().inUse(false);
    // delete (*appIt)->game();
    // (*appIt)->game(0);
    // (*appIt)->menu()->inUse(true);
    (*appIt)->state(Client::MENU);
  }
  _menuOutput.push(new Callback<menu::Manager, menu::Game *>(_menuManager, thatGame->first,
							     &menu::Manager::endGame));
  _games.erase(thatGame);
  delete loadedGame;
}

void	Application::cancelGame(const game::Game *loadedGame)
{
  game::Game::client_list::const_iterator	gameIt;
  game_list::iterator				thatGame;

  thatGame = std::find_if(_games.begin(), _games.end(), PredicateGame(loadedGame));
  if (thatGame == _games.end())
    return;
#if defined(DEBUG)
  log << "Application::endGame(): " << thatGame->second << " End of Game..." << std::endl;
#endif
  for (gameIt = thatGame->second->clients().begin();
       gameIt != thatGame->second->clients().end(); ++gameIt)
  {
    client_list::iterator	appIt;

    appIt = std::find_if(_clients.begin(), _clients.end(), PredicateClient((*gameIt)->clientID()));
    // (*appIt)->game().inUse(true);
    // (*appIt)->menu().inUse(false);
    // delete (*appIt)->game();
    // (*appIt)->game(0);
    // (*appIt)->menu()->inUse(true);
    (*appIt)->state(Client::MENU);
  }
  _menuOutput.push(new Callback<menu::Manager, menu::Game *>(_menuManager, thatGame->first,
							     &menu::Manager::endGame));
  _games.erase(thatGame);
  delete loadedGame;
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

Application::PredicateClient::PredicateClient(requestCode::SessionID client):
  _client(client)
{

}

bool	Application::PredicateClient::operator()(const Client *src)
{
  return (src->id() == _client);
}

Application::PredicateGame::PredicateGame(const game::Game *game) :
  _game(game)
{

}

bool	Application::PredicateGame::operator()(const game_pair &src)
{
  return (src.second == _game);
}
