#include	"Player.h"
#include	"game.h"


void						Player::draw(void)
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
		_image.setTextureRect(sf::IntRect(132, _indexSprite, 68, 38)); // nothing pos
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
			_image.setTextureRect(sf::IntRect(264, _indexSprite, 68, 38));
			break;
		case Down:
			_image.setTextureRect(sf::IntRect(0, _indexSprite, 68, 38));
			break;
		default:
			_image.setTextureRect(sf::IntRect(132, _indexSprite, 68, 38));
			break;
		}
	}
	_gameWindow->draw(_image);
}

void			Player::update(LookDirection lDir, int updtatedPos)
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


Player::Player(ObjType type, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow)
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
	_image.setTexture(*text);
	_image.setTextureRect(sf::IntRect(132, _indexSprite, 68, 38));
	_image.setPosition((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos));
	_mvtTime = 0.25f;
	_timerMvt = new Timer(new sf::Time(sf::seconds(_mvtTime)));
	_gameWindow = gameWindow;
	_act = false;
	_action = Nothing;
}
