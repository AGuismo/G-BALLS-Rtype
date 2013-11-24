#include		"BydosLaser.h"
#include		"game.h"

void						BydosLaser::draw(void)
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
		_image.setPosition((float)Game::POSX(_cCurPos) + 30.0f, (float)Game::POSY(_cCurPos) + 10.0f);
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
		_image.setPosition(_vCurPos.x + 30.0f, _vCurPos.y + 10.0f);
	}
	_image.setTextureRect(_laserAnimation.getFrame());
	if (_timerAlive.isEnded())
		_alive = false;
	_gameWindow->draw(_image);
}

void			BydosLaser::update(LookDirection lDir, int updtatedPos)
{
	(void)lDir;
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


BydosLaser::BydosLaser(ObjType type, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow) : _laserAnimation(0.05f)
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
	_image.setPosition((float)Game::POSX(_cCurPos) + 20.0f, (float)Game::POSY(_cCurPos) + 5.0f);
	_mvtTime = 0.25f;
	_timerAlive = Timer(sf::seconds(Game::ALIVE_TIMER));
	_timerMvt = Timer(sf::seconds(_mvtTime));
	_gameWindow = gameWindow;
	_act = false;
	_action = Nothing;
	_image.setTextureRect(sf::IntRect(0, 80, 100, 14));
	_laserAnimation.addFrame(sf::IntRect(0, 80, 101, 14));
	_laserAnimation.addFrame(sf::IntRect(100, 80, 100, 14));
	_laserAnimation.addFrame(sf::IntRect(200, 80, 100, 14));
}

void				BydosLaser::onDestruction(Game &game)
{
  (void)game;
}
