#include		"Bydos1.h"
#include		"game.h"

void						Bydos1::draw(void)
{

	if ((_vCurPos.x == _vNextPos.x && _vCurPos.y == _vNextPos.y) ||
		_timerMvt->isEnded() || _cCurPos == _cNextPos)
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
		findAnimation();
		if (_vCurPos.x < _vNextPos.x)
			_vCurPos.x += (_vLag * Game::OBJ_DEC_X_FRAME);
		if (_vCurPos.x > _vNextPos.x)
			_vCurPos.x -= (_vLag * Game::OBJ_DEC_X_FRAME);
		if (_vCurPos.y < _vNextPos.y)
			_vCurPos.y += (_vLag * Game::OBJ_DEC_Y_FRAME);
		if (_vCurPos.y > _vNextPos.y)
			_vCurPos.y -= (_vLag * Game::OBJ_DEC_Y_FRAME);
		_image.setPosition(_vCurPos.x, _vCurPos.y);
		switch (_action)
		{
		case Up:
			_image.setTextureRect(_leftAnimation->getFrame());
			break;
		case Down:
			_image.setTextureRect(_leftAnimation->getFrame());
			break;
		case Left:
			_image.setTextureRect(_leftAnimation->getFrame());
			break;
		case Right:
			_image.setTextureRect(_rightAnimation->getFrame());
			break;
		default:
			break;
		}
	}
	_gameWindow->draw(_image);
}

void			Bydos1::update(Action act, LookDirection lDir, int updtatedPos)
{
	if ((act != Nothing && _act) || (updtatedPos != Game::UNCHANGED))
	{
		_cNextPos = updtatedPos;
		if (!_act)
		{
			_act = true;
			_vLag = 1.0f;
			_vCurPos.x = (float)Game::POSX(_cCurPos);
			_vCurPos.y = (float)Game::POSY(_cCurPos);
			_timerMvt->restart();
		}
		else if (_act)
		{
			if (_vLag < Game::MAX_VLAG)
				_vLag += Game::VLAG;
			_timerMvt->restart();
		}
		_vNextPos.x = (float)Game::POSX(_cNextPos);
		_vNextPos.y = (float)Game::POSY(_cNextPos);
	}
}


Bydos1::Bydos1(ObjType type, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow)
{
	_type = type;
	_id = id;
	_texture = text;
	_cCurPos = pos;
	_cNextPos = pos;
	_ld = ld;
	_vCurPos = sf::Vector2f((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos));
	_vNextPos = sf::Vector2f((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos));
	_image.setTexture(*text);
	_image.setTextureRect(sf::IntRect(0, 0, 48, 72));
	_image.setPosition((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos));
	_mvtTime = 0.60f;
	_timerMvt = new Timer(new sf::Time(sf::seconds(_mvtTime)));
	_gameWindow = gameWindow;
	_act = false;
	_action = Nothing;
	_leftAnimation = new Animation(0.05f);
	_rightAnimation = new Animation(0.05f);
	_leftAnimation->addFrame(sf::IntRect(0, 15, 66, 72));
	_leftAnimation->addFrame(sf::IntRect(66, 15, 66, 72));
	_leftAnimation->addFrame(sf::IntRect(132, 15, 66, 72));
	_leftAnimation->addFrame(sf::IntRect(198, 15, 66, 72));
	_leftAnimation->addFrame(sf::IntRect(264, 15, 66, 72));
	_leftAnimation->addFrame(sf::IntRect(330, 15, 66, 72));
	_leftAnimation->addFrame(sf::IntRect(396, 15, 66, 72));
	_leftAnimation->addFrame(sf::IntRect(462, 15, 66, 72));
	_rightAnimation->addFrame(sf::IntRect(536, 15, 66, 72));
	_rightAnimation->addFrame(sf::IntRect(602, 15, 66, 72));
	_rightAnimation->addFrame(sf::IntRect(666, 15, 66, 72));
	_rightAnimation->addFrame(sf::IntRect(734, 15, 66, 72));
	_rightAnimation->addFrame(sf::IntRect(800, 15, 66, 72));
	_rightAnimation->addFrame(sf::IntRect(866, 15, 66, 72));
	_rightAnimation->addFrame(sf::IntRect(932, 15, 66, 72));
	_rightAnimation->addFrame(sf::IntRect(998, 15, 66, 72));
}