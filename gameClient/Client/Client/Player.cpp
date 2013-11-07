#include	"Player.h"
#include	"Game.h"

// special event < < < < WARNING
//act lock qui bifurque le _pos par => init le vector T0 et le vector Arrivé et a chaque update de draw ++10 tant que TO <= arrivé puis delock _pos classique


void			Player::draw(void)
{
	_image.setPosition((float)Game::POSX(_pos), (float)Game::POSY(_pos));
	_gameWindow->draw(_image);
}

void			Player::update(Action act)
{
	_act = (act != Nothing) ? true : false;

	std::cout << "elapsed " <<_mvtClock.getElapsedTime().asSeconds() << " mvt " << _mvTime << std::endl;
	if (_act == true && _mvtClock.getElapsedTime().asSeconds() > _mvTime)
	{
		switch (act)
		{
		case Left:
			_pos = (_pos % Game::SIZE_GAME_BOARD == 0) ? _pos : _pos - 1;
			_mvtClock.restart();
			break;
		case Right:
			_pos = ((_pos + 1) % Game::SIZE_GAME_BOARD == 0) ? _pos : _pos + 1;
			_mvtClock.restart();
			break;
		case Up:
			_pos = (_pos / Game::SIZE_GAME_BOARD == 0) ? _pos : _pos - Game::SIZE_GAME_BOARD;
			_image.setTextureRect(sf::IntRect(264, _indexSprite, 68, 38));
			_mvtClock.restart();
			break;
		case Down:
			_pos = (_pos + Game::SIZE_GAME_BOARD > Game::CASE_GAME_BOARD) ? _pos : _pos + Game::SIZE_GAME_BOARD;
			_image.setTextureRect(sf::IntRect(0, _indexSprite, 68, 38));
			_mvtClock.restart();
			break;
/*		case Nothing:
			_image.setTextureRect(sf::IntRect(132, _indexSprite, 68, 38));
			break;*/
		default:
			break;
		}
	}
	else if (!_act)
	{
		_image.setTextureRect(sf::IntRect(132, _indexSprite, 68, 38));
		_mvtClock.restart();
	}

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
	_image.setTextureRect(sf::IntRect(132, _indexSprite, 68, 38));
	_image.setPosition((float)Game::POSX(_pos), (float)Game::POSY(_pos));
	_act = false;
	_mvTime = 0.04;
}