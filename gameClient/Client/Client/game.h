#ifndef GAME
# define	GAME

#include	<deque>

#include	"TextureManager.h"
#include	"LayerManager.h"
#include	"AudioManager.h"
#include	"Factory.h"

class gameWindow;
class Factory;

class Game
{
private:
	sf::RenderWindow			*_gameWindow;
	sf::Event					*_event;

private:
	typedef std::deque<AObject *> obj_type;

private:
	Factory						_factory;
	TextureManager				_textureManager;
	LayerManager				_layerManager;
	AudioManager				_audioManager;
	obj_type					_objects;
	int							_idPlayer;

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
	void						draw(void);
	void						update(void);
	bool						updatePlayer(Action action);

public:
	bool						load(void);
	void						run(void);
	bool						addObj(ObjType type, int id, int pos);

public:
	Game(sf::RenderWindow *gameWindow, sf::Event *event);
	~Game() {}

private:
	Game(const Game &);
	Game					operator=(const Game &);
};

#endif // !GAME
