#ifndef GAME
# define	GAME

#include	<deque>

#include	"TextureManager.h"
#include	"LayerManager.h"
#include	"AudioManager.h"
#include	"Factory.h"

class gameWindow;
class Factory;

namespace network
{
  class	Manager;
}

class Game
{
private:
  typedef std::deque<AObject *> obj_type;

private:
  sf::RenderWindow			*_gameWindow;
  sf::Event				*_event;
  game::TextureManager			_textureManager;
  obj_type				_objects;
  int					_idPlayer;
  Factory				_factory;
  LayerManager				_layerManager;
  AudioManager				_audioManager;
  network::Manager			&_network;

public:
  static const int			SIZE_GAME_BOARD = 16;
  static const int			CASE_GAME_BOARD = 255;
  static const int			PX_DEC_X = 81;
  static const int			PX_DEC_Y = 46;

public:
  static const float			OBJ_DEC_X_FRAME;
  static const float			OBJ_DEC_Y_FRAME;

public:
  static const float			VLAG;
  static const float			MAX_VLAG;

public:
  static const int			UNCHANGED = -42;

public:
  static int					POSX(int x) { return ((x % SIZE_GAME_BOARD) * PX_DEC_X); }
  static int					POSY(int y) { return ((y / SIZE_GAME_BOARD) * PX_DEC_Y); }

private:
  bool						updatePlayer(Action action);

private:
  void						drawObjects(void);
  void						cleanObjects(void);

private:
  void						cleanGame(void);

public:
  bool						updateObj(ObjType type, LookDirection lDir, int id, int pos);
  bool						addObj(ObjType type, int id, int pos);
  bool						delObj(int id);

public:
  bool						load(void);
  void						run(void);


public:
  Game(sf::RenderWindow *gameWindow, sf::Event *event, network::Manager &);
  ~Game();

private:
  Game(const Game &);
  Game					operator=(const Game &);
};

#endif // !GAME
