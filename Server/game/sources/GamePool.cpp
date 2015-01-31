#if defined(DEBUG)
# include	<iostream>
#endif // !DEBUG
#include	<ctime>
#include	<algorithm>
#include	"AGameRequest.hh"
#include	"GamePool.hh"
#include	"Game.hh"
#include	"GameManager.hh"
#include	"ICallbacks.hh"
#include	"Callback.hh"
#include	"Application.hh" // Log purpose

using namespace game;

size_t GamePool::incrementalID = 1;

////////////////////////////
// Constructor/Destructor //
////////////////////////////

GamePool::GamePool(Manager *parent, output_event &output):
  poolID(incrementalID++), _parent(parent), _active(false),
  _th(Func::Bind(&GamePool::routine, this)), _output(output)
{

}

GamePool::~GamePool()
{
}

//////////////////////////
// Pool Start/Stop/Join //
//////////////////////////
void			GamePool::join()
{
  _th.join();
}

void			GamePool::stop()
{
  _active = false;
}

void			GamePool::run()
{
  _active = true;
  _th.run();
#if defined(DEBUG)
  Application::log << "Pool manager " << this << " started..." << std::endl;
#endif
}

bool			GamePool::full() const
{
  return (_games.size() == MAX_GAMES);
}

//////////////////////////////////
// Send/Recv Request Management //
//////////////////////////////////

GamePool::input_event	&GamePool::input()
{
  return (_input);
}

void	GamePool::dispatchMessages(AGameRequest *req)
{
  for (game_list::iterator itGame = _games.begin(); itGame != _games.end(); ++itGame)
  {
    Game::client_list	&clients = (*itGame)->clients();

    for (Game::client_list::iterator itCli = clients.begin(); itCli != clients.end(); ++itCli)
    {
      if (req->SessionID() == (*itCli)->clientID())
      {
	(*itCli)->requestPushInput(req);
	return ;
      }
    }
  }
}

void	GamePool::newGame(Game *game)
{
  if (_games.size() < MAX_GAMES)
  {
#if defined(DEBUG)
    Application::log << "GamePool(" << poolID << ")::newGame -> " << game << std::endl;
#endif
    _games.push_back(game); // The clock of new game is on the max, so other games clock are less.
  }
}

/////////////
// Routine //
/////////////

void		GamePool::executeCallback()
{
  ICallbacks	*cb;
  bool		timeout = false;

  if (_games.empty())
    cb = _input.pop();
  else
    cb = _input.pop(_games.front()->timer().tv_usec / 1000UL, timeout);
#if defined(DEBUG)
  Application::log << std::boolalpha << "GamePool(" << poolID
	    << ")::executeCallback -> timeout ? " << timeout << std::endl;
#endif
  if (!timeout)
  {
    (*cb)();
    delete cb;
  }
}


void	GamePool::routine(GamePool *self)
{
  self->_clock.restart();
  while (self->_active)
  {
#if defined(DEBUG)
    Application::log << "GamePool(" << self->poolID << ")::routine" << std::endl;
#endif
    self->executeCallback();
    Time	elapsedTime = self->_clock.restart();
    self->updateGameClocks(elapsedTime);
    self->updateGame();

    // Si un jeu tourne, mettre un timeout sur la prochain jeu a mettre à jour dans l'eventQueue.
    // Sinon, bloquer indéfiniement l'eventQueue.
    // Exécuter les Callback envoyé par le GameManager
    // Mettre à jour la clock pour savoir le temps que l'on a passé bloqué.
    // Mettre à jour les clocks des jeux
    // Exécuter les clients avec leur clock à Zéro.




    // if (!self->_games.empty())
    // 	self->_monitor.setOption(net::streamManager::TIMEOUT, self->_games.front()->timer());
    // else
    // {
    // 	struct	timeval	def;
    // 	def.tv_sec = 1;
    // 	def.tv_usec = 0;
    // 	self->_monitor.setOption(net::streamManager::TIMEOUT, def);
    // }
    // self->_monitor.run(); /* Surcouche du select() */
    // self->_clock.update();
    // self->updateGameClocks(self->_clock.getElapsedTime());
    // self->updateCallback();
    // if (self->_server.read() || self->_server.write())
    // {
    // 	try
    // 	{
    // 	  if (self->_server.read())
    // 	    self->readData();
    // 	  if (self->_server.write())
    // 	    self->writeData();
    // 	}
    // 	catch (net::Exception &e)
    // 	{
    // 	  Application::log << "Error " << e.what() << "in Manager::routine." << std::endl << std::endl;
    // 	}
    // }
    // if (self->_monitor.isTimeout())
    // {
    // 	self->update();
    // }
  }
}

void		GamePool::updateGameClocks(const Time &time)
{
  for (game_list::iterator it = _games.begin(); it != _games.end(); it++)
  {
    (*it)->timer().tv_usec -= time.asMicroseconds();
    if ((*it)->timer().tv_usec < 0)
      (*it)->timer().tv_usec = 0;
  }
}

void		GamePool::updateGame()
{
  while (!_games.empty() && _games.front()->timer().tv_usec == 0)
  {
    Game	*game = _games.front();

    _games.pop_front();
    game->update();
    if (game->status() == Game::IN_GAME || game->status() == Game::WAITING_PLAYER)
      _games.push_back(game);
#if defined(DEBUG)
    else
      Application::log << "GamePool::updateGame() - Game " << game << " has just finished" << std::endl;
#endif // !DEBUG
  }
}

void		GamePool::cancelGame(const Game *game)
{
  _output.push(new Callback<Manager, const Game *>(_parent, game, &Manager::cancelGame));
#if defined(DEBUG)
  Application::log << "GamePool::cancelGame() - Game " << game << " has just been cancelled" << std::endl;
#endif // !DEBUG
}

void		GamePool::endGame(const Game *game)
{
  _output.push(new Callback<Manager, const Game *>(_parent, game, &Manager::endGame));
#if defined(DEBUG)
  Application::log << "GamePool::endGame() - Game " << game << " has just been ended" << std::endl;
#endif // !DEBUG
}

Manager		*GamePool::parent() const
{
  return (_parent);
}
