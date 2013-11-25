#include		"Slider.h"
#include		"game.h"

using namespace requestCode::game;

void						Slider::draw(void)
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
		_image.setPosition((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos));
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
		_image.setPosition(_vCurPos.x, _vCurPos.y);
	}
	if (_ld == requestCode::game::client::EAST)
		_image.setTextureRect(_rightAnimation.getFrame());
	else
		_image.setTextureRect(_leftAnimation.getFrame());
	if (_timerAlive.isEnded())
		_alive = false;
	_gameWindow->draw(_image);
}

void			Slider::update(game::Dir lDir, int updtatedPos)
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


Slider::Slider(game::Type type, int id, int pos, game::Dir ld, sf::Texture *text, sf::RenderWindow *gameWindow) :
_leftAnimation(0.20f), _rightAnimation(0.14f)
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
	_image.setPosition((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos));
	_mvtTime = 0.60f;
	_timerAlive = Timer(sf::seconds(Game::ALIVE_TIMER));
	_timerMvt = Timer(sf::seconds(_mvtTime));
	_gameWindow = gameWindow;
	_act = false;
	_action = Nothing;
	_leftAnimation.addFrame(sf::IntRect(0, 0, 66, 68));
	_leftAnimation.addFrame(sf::IntRect(66, 0, 66, 68));
	_leftAnimation.addFrame(sf::IntRect(132, 0, 66, 68));
	_leftAnimation.addFrame(sf::IntRect(198, 0, 66, 68));
	_leftAnimation.addFrame(sf::IntRect(264, 0, 66, 68));
	_leftAnimation.addFrame(sf::IntRect(330, 0, 66, 68));
	_leftAnimation.addFrame(sf::IntRect(396, 0, 66, 68));
	_leftAnimation.addFrame(sf::IntRect(462, 0, 66, 68));
	_rightAnimation.addFrame(sf::IntRect(0, 68, 66, 68));
	_rightAnimation.addFrame(sf::IntRect(66, 68, 66, 68));
	_rightAnimation.addFrame(sf::IntRect(132, 68, 66, 68));
	_rightAnimation.addFrame(sf::IntRect(198, 68, 66, 68));
	_rightAnimation.addFrame(sf::IntRect(264, 68, 66, 68));
	_rightAnimation.addFrame(sf::IntRect(330, 68, 66, 68));
	_rightAnimation.addFrame(sf::IntRect(396, 68, 66, 68));
	_rightAnimation.addFrame(sf::IntRect(462, 68, 66, 68));
}

void				Slider::onDestruction(Game &game)
{
  game.addObj(server::NORMAL_BANG, Game::generateId(), _cCurPos);
	AudioManager::getInstance().play(ABYDOS_DESTRUCTION);
}
