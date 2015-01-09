#include	"Scenario.hh"

const float	Scenario::DEFAULT_SPEED = 1.0f;

Scenario::Scenario(unsigned short height, unsigned short width, float speed, IReferee::Difficulty difficulty)
{
	_map.height = height;
	_map.width = width;
	_game.speed = speed;
	_game.difficulty = difficulty;
}

Scenario::~Scenario()
{
}

Scenario::Scenario(const Scenario &src)
{
	_map.height = src._map.height;
	_map.width = src._map.width;
	_game.speed = src._game.speed;
	_game.difficulty = src._game.difficulty;
	_players = src._players;
}

Scenario		&Scenario::operator=(const Scenario &src)
{
	if (&src != this)
	{
		_map.height = src._map.height;
		_map.width = src._map.width;
		_game.speed = src._game.speed;
		_game.difficulty = src._game.difficulty;
		_players = src._players;
	}
	return (*this);
}

void		Scenario::addPlayer(const Player &p)
{
	_players.push_back(p);
}

const std::vector<Player>	&Scenario::getPlayers() const
{
	return (_players);
}

void						Scenario::getMapSize(unsigned short &height, unsigned short &width)
{
	height = _map.height;
	width = _map.width;
}

void						Scenario::setMapSize(unsigned short height, unsigned short width)
{
	_map.height = height;
	_map.width = width;
}

void						Scenario::setGameSpeed(float speed)
{
	_game.speed = speed;
}

float						Scenario::getGameSpeed() const
{
	return (_game.speed);
}

void						Scenario::setDifficulty(IReferee::Difficulty difficulty)
{
	_game.difficulty = difficulty;
}

IReferee::Difficulty		Scenario::getDifficulty() const
{
	return (_game.difficulty);
}
