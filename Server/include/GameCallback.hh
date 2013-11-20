#ifndef GAMECALLBACK_H_
# define GAMECALLBACK_H_

# include	"ICallbacks.hh"
# include	"Bind.hpp"

class	Game;
class	Application;

class GameCallback : public ICallbacks
{
public:
  GameCallback(Game *game, void (Application::*)(Game *));
  virtual ~GameCallback();

public:
  void	operator()(Application *);

private:
  GameCallback(GameCallback const&);
  GameCallback& operator=(GameCallback const&);

protected:
  Function<void (Application::*)(Game *)>	_callback;
  Game						*_game;
};

#endif /* GAMECALLBACK_H_ */
