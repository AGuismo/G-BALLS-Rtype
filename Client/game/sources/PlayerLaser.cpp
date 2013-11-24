#include		"PlayerLaser.h"
#include		"game.h"

void						PlayerLaser::draw(void)
{

	if ((_vCurPos.x == _vNextPos.x && _vCurPos.y == _vNextPos.y) ||
		_timerMvt.isEnded() || _cCurPos == _cNextPos)
	{
		_act = false;
		_action = Nothing;
		_cCurPos = _cNextPos;
		_vCurPos.x = (float)Game::POSX(_cCurPos);
		_vCurPos.y = (float)Game::POSY(_cCurPos);
		_vNextPos = _vCurPos;
		_image.setPosition((float)Game::POSX(_cCurPos) + 15.0f, (float)Game::POSY(_cCurPos) + 8.0f);
	}
	else if (_act)
	{
		if (_vCurPos.x < _vNextPos.x)
			_vCurPos.x += (_vLag * Game::OBJ_DEC_X_FRAME);
		if (_vCurPos.x > _vNextPos.x)
			_vCurPos.x -= (_vLag * Game::OBJ_DEC_X_FRAME);
		if (_vCurPos.y < _vNextPos.y)
			_vCurPos.y += (_vLag * Game::OBJ_DEC_Y_FRAME);
		if (_vCurPos.y > _vNextPos.y)
			_vCurPos.y -= (_vLag * Game::OBJ_DEC_Y_FRAME);
		_image.setPosition(_vCurPos.x +15.0f, _vCurPos.y +8.0f);
		switch (_ld)
		{
		case East:
			_image.setTextureRect(sf::IntRect(565, 115, 35, 24));
			break;
		case West:
			_image.setTextureRect(sf::IntRect(600, 115, 35, 24));
			break;
		case NorthEast:
			_image.setTextureRect(sf::IntRect(530, 186, 35, 24));
			break;
		case SouthEast:
			_image.setTextureRect(sf::IntRect(565, 186, 35, 24));
			break;
		case SouthWest:
			_image.setTextureRect(sf::IntRect(600, 186, 35, 24));
			break;
		case NorthWest:
			_image.setTextureRect(sf::IntRect(635, 186, 35, 24));
			break;
		default:
			_image.setTextureRect(sf::IntRect(565, 115, 35, 24));
			break;
		}
	}
	if (_timerAlive.isEnded())
		_alive = false;
	_gameWindow->draw(_image);
}


void			PlayerLaser::update(LookDirection lDir, int updtatedPos)
{
	_ld = lDir;
	if (updtatedPos != Game::UNCHANGED)
	{
		_cNextPos = updtatedPos;
		if (!_act)
		{
			_act = true;
			_vLag = 1.0f;
			_vCurPos.x = (float)Game::POSX(_cCurPos);
			_vCurPos.y = (float)Game::POSY(_cCurPos);
			_timerMvt.restart();
		}
		else if (_act)
		{
			if (_vLag < Game::MAX_VLAG)
				_vLag += Game::VLAG;
			_timerMvt.restart();
		}
		_vNextPos.x = (float)Game::POSX(_cNextPos);
		_vNextPos.y = (float)Game::POSY(_cNextPos);
	}
	_timerAlive.restart();
}


PlayerLaser::PlayerLaser(ObjType type, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow)
{
	_type = type;
	_id = id;
	_texture = text;
	_cCurPos = pos;
	_cNextPos = pos;
	_ld = ld;
	_alive = true;
	_vCurPos = sf::Vector2f((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos));
	_vNextPos = sf::Vector2f((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos));
	_image.setTexture(*text);
	_image.setTextureRect(sf::IntRect(565, 115, 35, 24));
	_mvtTime = 0.25f;
	_timerAlive = Timer(sf::seconds(Game::ALIVE_TIMER));
	_timerMvt = Timer(sf::seconds(_mvtTime));
	_gameWindow = gameWindow;
	_act = false;
	_action = Nothing;
}

void				PlayerLaser::onDestruction(Game &game)
{
  (void)game;
}
