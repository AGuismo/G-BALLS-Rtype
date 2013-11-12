#include	"Player.h"
#include	"Game.h"

// special event < < < < WARNING
//act lock qui bifurque le _pos par => init le vector T0 et le vector Arrivé et a chaque update de draw ++10 tant que TO <= arrivé puis delock _pos classique


void			Player::draw(void)
{


	if ((_curPos->x == _goalPos->x && _curPos->y == _goalPos->y) || _timerMvt->isEnded())
	{
		_pos = _nextPos;
		_curPos->x = (float)Game::POSX(_pos);
		_curPos->y = (float)Game::POSY(_pos);
		_goalPos->x = (float)Game::POSX(_pos);
		_goalPos->y = (float)Game::POSY(_pos);
		_image.setPosition((float)Game::POSX(_pos), (float)Game::POSY(_pos));
		_act = false;
//		std::cout << "ARRIVED" << std::endl;
	}
	else
	{
		if (_curPos->x < _goalPos->x)
			_curPos->x += 16.02f;
		if (_curPos->x > _goalPos->x)
			_curPos->x -= 16.02f;
		if (_curPos->y < _goalPos->y)
			_curPos->y += 5.35f;
		if (_curPos->y > _goalPos->y)
			_curPos->y -= 5.75f;
		_act = true;
		_image.setPosition(_curPos->x, _curPos->y);
	}
	_gameWindow->draw(_image);
	//_image.setPosition((float)Game::POSX(_pos), (float)Game::POSY(_pos));
}

void			Player::update(Action act)
{
	bool test;
	test = (act != Nothing) ? true : false;
	if (test == true  /*&&  _timer->isEnded()*/)
	{
		if (!_act)
		{
			_curPos->x = (float)Game::POSX(_pos);
			_curPos->y = (float)Game::POSY(_pos);
			_act = true;
			_timerMvt->restart();
		}
		else
		{
			_curPos->x = _goalPos->x;
			_curPos->y = _goalPos->y;
		}
//		_act = true;
		switch (act)
		{
		case Left:
			_nextPos = (_pos % Game::SIZE_GAME_BOARD == 0) ? _pos : _pos - 1;
			_goalPos->x = (float)Game::POSX(_nextPos);
			_goalPos->y = (float)Game::POSY(_nextPos);
			break;
		case Right:
			_nextPos = ((_pos + 1) % Game::SIZE_GAME_BOARD == 0) ? _pos : _pos + 1;
			_goalPos->x = (float)Game::POSX(_nextPos);
			_goalPos->y = (float)Game::POSY(_nextPos);
			std::cout << "Right: curpos[" << _curPos->x << ":" << _curPos->y << "] " << "nextpos[" << _goalPos->x << ":" << _goalPos->y << "] " << std::endl;
			break;
		case Up:
			_nextPos = (_pos / Game::SIZE_GAME_BOARD == 0) ? _pos : _pos - Game::SIZE_GAME_BOARD;
			_image.setTextureRect(sf::IntRect(264, _indexSprite, 68, 38));
			_goalPos->x = (float)Game::POSX(_nextPos);
			_goalPos->y = (float)Game::POSY(_nextPos);
			std::cout << "Up: curpos[" << _curPos->x << ":" << _curPos->y << "] " << "nextpos[" << _goalPos->x << ":" << _goalPos->y << "] " << std::endl;
			break;
		case Down:
			_nextPos = (_pos + Game::SIZE_GAME_BOARD > Game::CASE_GAME_BOARD) ? _pos : _pos + Game::SIZE_GAME_BOARD;
			_image.setTextureRect(sf::IntRect(0, _indexSprite, 68, 38));
			_goalPos->x = (float)Game::POSX(_nextPos);
			_goalPos->y = (float)Game::POSY(_nextPos);
			break;
		default:
			break;
		}
		if (act != Nothing)
		{
           //			_timerMvt->restart();
			//			_timer->restart();
		}

	}
	else if (!_act)
	{
//		_curPos->x = _goalPos->x;
//		_curPos->y = _goalPos->y;
		_image.setTextureRect(sf::IntRect(132, _indexSprite, 68, 38));
		_timer->restart();
	}

}

Player::Player(ObjType type, int id, int pos, LookDirection ld, sf::Texture *text, sf::RenderWindow *gameWindow)
{
	_type = type;
	_texture = text;
	_pos = pos;
	_nextPos = pos;
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
	_mvTime = 0.45f;
	_timer = new Timer(new sf::Time(sf::seconds(_mvTime)));
	_timerMvt = new Timer(new sf::Time(sf::seconds(0.30f)));
	_curPos = new sf::Vector2f(-42, -42);
	_goalPos = new sf::Vector2f(-42, -42);
}