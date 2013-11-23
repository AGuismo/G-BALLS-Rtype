#include		"BydosPlasma.h"
#include		"game.h"

void						BydosPlasma::draw(void)
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
		_image.setPosition((float)Game::POSX(_cCurPos) + 20.0f, (float)Game::POSY(_cCurPos) + 5.0f);
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
		_image.setPosition(_vCurPos.x +20.0f, _vCurPos.y +5.0f);
	}
	_image.setTextureRect(_plasmaAnimation.getFrame());
	_gameWindow->draw(_image);
}

void			BydosPlasma::update(LookDirection lDir, int updtatedPos)
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
}


BydosPlasma::BydosPlasma(ObjType type, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow) :
  _plasmaAnimation(0.1f)
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
	_image.setPosition((float)Game::POSX(_cCurPos) + 20.0f, (float)Game::POSY(_cCurPos) +5.0f);
	_mvtTime = 0.25f;
	_timerMvt = Timer(sf::seconds(_mvtTime));
	_gameWindow = gameWindow;
	_act = false;
	_action = Nothing;
	_image.setTextureRect(sf::IntRect(267, 6, 25, 20));
	_plasmaAnimation.addFrame(sf::IntRect(267, 6, 25, 20));
	_plasmaAnimation.addFrame(sf::IntRect(299, 6, 25, 20));
	_plasmaAnimation.addFrame(sf::IntRect(331, 6, 25, 20));
	_plasmaAnimation.addFrame(sf::IntRect(364, 6, 26, 20));
}

void				BydosPlasma::onDestruction(Game &game)
{
}