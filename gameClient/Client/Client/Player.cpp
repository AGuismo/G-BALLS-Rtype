#include	"Player.h"
#include	"Game.h"


void			Player::draw(void)
{
	_gameWindow->draw(_image);
}

void			Player::update(Action act)
{
	switch (act)
	{
	case Left:
		_pos = (_pos % Game::SIZE_GAME_BOARD == 0) ? _pos : _pos - 1;
		break;
	case Right:
		_pos = ((_pos + 1) % Game::SIZE_GAME_BOARD == 0) ? _pos : _pos + 1;
		break;
	case Up:
		_pos = (_pos / Game::SIZE_GAME_BOARD == 0) ? _pos : _pos - Game::SIZE_GAME_BOARD;
		break;
	case Down:
		_pos = (_pos + Game::SIZE_GAME_BOARD > Game::CASE_GAME_BOARD) ? _pos : _pos + Game::SIZE_GAME_BOARD;
		break;
	default:
		break;
	}
	_image.setPosition((float)Game::POSX(_pos), (float)Game::POSY(_pos));
}

Player::Player(ObjType type, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow)
{
	_type = type;
	_texture = text;
	_pos = pos;
	_id = id;
	_ld = ld;
	_indexSprite = 0;

	switch (type)
	{
	case PLAYER1:
		_indexSprite = 0;
		break;
	case PLAYER2:
		_indexSprite = 34;
		break;
	case PLAYER3:
		_indexSprite = 68;
		break;
	case PLAYER4:
		_indexSprite = 102;
		break;
	default:
		break;
	}
	_gameWindow = gameWindow;
	_image.setTexture(*text);

	_image.setTextureRect(sf::IntRect(132, _indexSprite, 68, 40));
	_image.setPosition((float)Game::POSX(_pos), (float)Game::POSY(_pos));
}