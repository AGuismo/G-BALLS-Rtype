#include	"Player.h"
#include	"Game.h"

// special event < < < < WARNING

void			Player::draw(void)
{
	if ((_vCurPos->x == _vNextPos->x && _vCurPos->y == _vNextPos->y) ||
		_timerMvt->isEnded() ||
		_cCurPos == _cNextPos)
	{
		_cCurPos = _cNextPos;
		_act = false;
		_vCurPos->x = (float)Game::POSX(_cCurPos);
		_vCurPos->y = (float)Game::POSY(_cCurPos);
		_vNextPos->x = (float)Game::POSX(_cCurPos);
		_vNextPos->y = (float)Game::POSY(_cCurPos);
		_image.setPosition((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos));
	}
	else
	{
		if (_vCurPos->x < _vNextPos->x)
			_vCurPos->x += (_vLag * Game::PX_DEC_X / 12.0f);
		if (_vCurPos->x > _vNextPos->x)
			_vCurPos->x -= (_vLag * Game::PX_DEC_X / 12.0f);
		if (_vCurPos->y < _vNextPos->y)
			_vCurPos->y += (_vLag * Game::PX_DEC_Y / 12.0f);
		if (_vCurPos->y > _vNextPos->y)
			_vCurPos->y -= (_vLag * Game::PX_DEC_Y / 12.0f);
		_act = true;
		_image.setPosition(_vCurPos->x, _vCurPos->y);
	}
	_gameWindow->draw(_image);
}

void			Player::update(Action act, int updtatedPos)
{
	if ((act == Nothing && !_act) || updtatedPos == Game::UNCHANGED)
		_image.setTextureRect(sf::IntRect(132, _indexSprite, 68, 38));
	else
	{
		if (!_act)
		{
			_act = true;
			_vLag = 1.0f;
			_cNextPos = updtatedPos;
			_vCurPos->x = (float)Game::POSX(_cCurPos);
			_vCurPos->y = (float)Game::POSY(_cCurPos);
			_vNextPos->x = (float)Game::POSX(_cNextPos);
			_vNextPos->y = (float)Game::POSY(_cNextPos);
			_timerMvt->restart();
		}
		else if (_act)
		{
			std::cout << "action en cours" << std::endl;
			_cNextPos = updtatedPos;
			_vNextPos->x = (float)Game::POSX(_cNextPos);
			_vNextPos->y = (float)Game::POSY(_cNextPos);
			_act = true;
			if (_vLag < Game::MAX_VLAG)
				_vLag += Game::VLAG;
			_timerMvt->restart();
			std::cout << "Up: curpos[" << _cCurPos << "] " << "nextpos[" <<  _cNextPos << "] vlage:[" << _vLag << "]" << std::endl;
			std::cout << "Up: curpos[" << _vCurPos->x << ":" << _vCurPos->y << "] " << "nextpos[" << _vNextPos->x << ":" << _vNextPos->y << "] " << std::endl;


		}
	}
}

const sf::Vector2f		*Player::getVectorNextPos(void)
{
	return (_vNextPos);
}

const sf::Vector2f		*Player::getVectorCurPos(void)
{
	return (_vNextPos);
}

const int				Player::getCaseNextPos(void)
{
	return (_cNextPos);
}

const int				Player::getCaseCurPos(void)
{
	return (_cNextPos);
}

Player::Player(ObjType type, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow)
{
	_type = type;
	_texture = text;
	_cCurPos = pos;
	_cNextPos = pos;
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
	_image.setPosition((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos));
	_act = false;
	_mvtTime = 0.42f;
	_timer = new Timer(new sf::Time(sf::seconds(0.45f)));
	_timerMvt = new Timer(new sf::Time(sf::seconds(_mvtTime)));
	_vCurPos = new sf::Vector2f((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos));
	_vNextPos = new sf::Vector2f((float)Game::POSX(_cCurPos), (float)Game::POSY(_cCurPos));
}




/*		switch (act)
{
case Left:
_cNextPos = (_cCurPos % Game::SIZE_GAME_BOARD == 0) ? _cCurPos : _cCurPos - 1;
_vNextPos->x = (float)Game::POSX(_cNextPos);
_vNextPos->y = (float)Game::POSY(_cNextPos);
break;
case Right:
_cNextPos = ((_cCurPos + 1) % Game::SIZE_GAME_BOARD == 0) ? _cCurPos : _cCurPos + 1;
_vNextPos->x = (float)Game::POSX(_cNextPos);
_vNextPos->y = (float)Game::POSY(_cNextPos);
std::cout << "Right: curpos[" << _vCurPos->x << ":" << _vCurPos->y << "] " << "nextpos[" << _vNextPos->x << ":" << _vNextPos->y << "] " << std::endl;
break;
case Up:
_cNextPos = (_cCurPos / Game::SIZE_GAME_BOARD == 0) ? _cCurPos : _cCurPos - Game::SIZE_GAME_BOARD;
_image.setTextureRect(sf::IntRect(264, _indexSprite, 68, 38));
_vNextPos->x = (float)Game::POSX(_cNextPos);
_vNextPos->y = (float)Game::POSY(_cNextPos);
std::cout << "Up: curpos[" << _vCurPos->x << ":" << _vCurPos->y << "] " << "nextpos[" << _vNextPos->x << ":" << _vNextPos->y << "] " << std::endl;
break;
case Down:
_cNextPos = (_cCurPos + Game::SIZE_GAME_BOARD > Game::CASE_GAME_BOARD) ? _cCurPos : _cCurPos + Game::SIZE_GAME_BOARD;
_image.setTextureRect(sf::IntRect(0, _indexSprite, 68, 38));
_vNextPos->x = (float)Game::POSX(_cNextPos);
_vNextPos->y = (float)Game::POSY(_cNextPos);
break;
default:
break;
}*/





















