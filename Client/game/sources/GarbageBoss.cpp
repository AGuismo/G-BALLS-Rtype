#include		"GarbageBoss.h"
#include		"game.h"

void						GarbageBoss::draw(void)
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
		_image.setTextureRect(sf::IntRect(0, 15, 66, 72));
		_image.setPosition((float)Game::POSX(_cCurPos) - 20.0F, (float)Game::POSY(_cCurPos) - 20.0F);
	}
	else if (_act)
	{
		findAnimation();
		if (_vCurPos.x < _vNextPos.x)
			_vCurPos.x += (_vLag * Game::OBJ_DEC_X_FRAME);
		if (_vCurPos.x > _vNextPos.x)
			_vCurPos.x -= (_vLag * Game::OBJ_DEC_X_FRAME);
		if (_vCurPos.y < _vNextPos.y)
			_vCurPos.y += (_vLag * Game::OBJ_DEC_Y_FRAME);
		if (_vCurPos.y > _vNextPos.y)
			_vCurPos.y -= (_vLag * Game::OBJ_DEC_Y_FRAME);
		_image.setPosition(_vCurPos.x - 20.0f, _vCurPos.y - 20.0f);
	}
	_image.setTextureRect(_GarbageBossAnimation.getFrame());
	_gameWindow->draw(_image);
}

void			GarbageBoss::update(LookDirection lDir, int updtatedPos)
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


GarbageBoss::GarbageBoss(ObjType type, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow) : _GarbageBossAnimation(0.35f)
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
	_image.setTextureRect(sf::IntRect(0, 0, 48, 72));
	_image.setPosition((float)Game::POSX(_cCurPos) - 20.0f, (float)Game::POSY(_cCurPos) - 20.0f);
	_mvtTime = 0.25f;
	_timerMvt = Timer(sf::seconds(_mvtTime));
	_gameWindow = gameWindow;
	_act = false;
	_action = Nothing;
	_GarbageBossAnimation.addFrame(sf::IntRect(0, 0, 364, 290));
	_GarbageBossAnimation.addFrame(sf::IntRect(378, 0, 364, 290));
}
