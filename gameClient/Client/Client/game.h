#ifndef GAME
# define	GAME

#include	<deque>

#include	"TextureManager.h"
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
	TextureManager				_textureManager;
	Factory						_factory;
	obj_type					_objects;
	int							_idPlayer;
private:
	sf::Texture					_bgTexture1;
	sf::Sprite					_bgImg1;
	sf::Texture					_bgTexture2;
	sf::Sprite					_bgImg2;

public:
	static const int			SIZE_GAME_BOARD = 16;
	static const int			CASE_GAME_BOARD = 255;
	static const int			PX_DEC_X = 81;
	static const int			PX_DEC_Y = 46;

public:
	static int					POSX(int x) { return ((x % SIZE_GAME_BOARD) * PX_DEC_X); }
	static int					POSY(int y) { return ((y / SIZE_GAME_BOARD) * PX_DEC_Y); }


private:
	void						draw(void);
	void						update(void);
	bool						updateObj(int id, Action action);

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
