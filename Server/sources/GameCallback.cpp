#include	"GameCallback.hh"
#include	"Application.hh"
#include	"Game.h"

GameCallback::GameCallback(Game *game, void (Application::*func)(Game *)) :
  _callback(func), _game(game)
{
}

GameCallback::~GameCallback()
{

}

void	GameCallback::operator()(Application *app)
{
  _callback(app, _game);
}
