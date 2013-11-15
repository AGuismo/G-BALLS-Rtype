#include	"Player.h"
#include	"Game.h"


void						Player::draw(void)
{
	if ((_vCurPos.x == _vNextPos.x && _vCurPos.y == _vNextPos.y) ||
		_timerMvt->isEnded() || _cCurPos == _cNextPos)
	{
		_act = false;
		_cCurPos = _cNextPos;
		_vCurPos.x = (float)Game::POSX(_cCurPos);
		_vCurPos.y = (float)Game::POSY(_cCurPos);
		_vNextPos = _vCurPos;
		_image.setTextureRect(sf::IntRect(132, _indexSprite, 68, 38)); // nothing pos
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
	_gameWindow->draw(_image);
}

void			Player::update(Action act, LookDirection lDir, int updtatedPos)
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

//_image.setTextureRect(sf::IntRect(132, _indexSprite, 68, 38));
/*			switch (act)
			{
			case Up:
				_image.setTextureRect(sf::IntRect(264, _indexSprite, 68, 38));
				break;
			case Down:
				_image.setTextureRect(sf::IntRect(0, _indexSprite, 68, 38));
			default:
				break;
			}
*/

Player::Player(ObjType type, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow)
{
	_type = type;
	_id = id;
	_texture = text;
	_cCurPos = pos;
	_cNextPos = pos;
	_ld = ld;
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
	_mvtTime = 0.42f;
	_timerMvt = new Timer(new sf::Time(sf::seconds(_mvtTime)));
	_gameWindow = gameWindow;
	_act = false;
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





















