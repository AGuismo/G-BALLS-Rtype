#ifndef GAME
# define	GAME

#include	<map>
#include	"TextureManager.hh"
#include	"LayerManager.hh"
#include	"AudioManager.hh"
#include	"Referee.hh"
#include	"Animation.hh"

class ARequest;

class Game
{
private:
  typedef std::map<unsigned short, Animation>	obj_map_type;
  typedef void	(Game::*game_callback)(const ARequest *);
  typedef std::map<requestCode::CodeID, game_callback>	callback_map;

  struct Texture
  {
	  std::string					ImagePath;
	  game::TextureManager::Key		TextureCode;
	  sf::IntRect					pos;

	  Texture(const std::string &ImagePath, const game::TextureManager::Key &TextureCode, const sf::IntRect &pos) :
		  ImagePath(ImagePath), TextureCode(TextureCode), pos(pos) {}
  };

private:
	LayerManager				_layerManager;
	obj_map_type				_objects;
	sf::RenderWindow			*_gameWindow;
	sf::Event					*_event;
	game::TextureManager		_textureManager;
	callback_map				_map;
	bool						_onGame;
	Referee						_referee;
	unsigned short				_stamp;

private:
  sf::Vector2f	PositionToVector2f(const Position &pos);
  Animation		&createAnimation(const Entity &object);
  Animation		&getAnimation(const Entity &object);
  void			drawObjects(void);
  void			draw(void);
  
  static void	onMoveLeft(sf::Keyboard::Key, Game *self);
  static void	onMoveRight(sf::Keyboard::Key, Game *self);
  static void	onMoveUp(sf::Keyboard::Key, Game *self);
  static void	onMoveDown(sf::Keyboard::Key, Game *self);
  static void	onFire(sf::Keyboard::Key, Game *self);
  static void	onEscape(sf::Keyboard::Key, Game *self);
  void			onMyselfMove(Position::dir dir);

private:
  void			cleanGame(void);

public:
  void			sendPlayerInfo() const;
  bool			updateObj(game::Type type, game::Dir lDir, int id, int pos);
  bool			addObj(game::Type type, int id, int pos);
  bool			delObj(int id);

public:
  bool			load(void);
  void			run(void);

private:
  void			elem(const ARequest *req);
  void			death(const ARequest *req);
  void			buff(const ARequest *req);
  void			score(const ARequest *req);
  void			victory(const ARequest *req);
  void			loose(const ARequest *req);
  void			nextStage(const ARequest *req);

public:
  Game(sf::RenderWindow *gameWindow, sf::Event *event);
  ~Game();

private:
  Game(const Game &);
  Game					operator=(const Game &);
};

#endif // !GAME
