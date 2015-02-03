#pragma once

#include	<vector>
#include	"Difficulty.hh"
#include	"Player.hh"

class Scenario
{
public:
  static const unsigned short	DEFAULT_WIDTH = 1920;
  static const unsigned short	DEFAULT_HEIGHT = 1080;
  static const float		DEFAULT_SPEED;
  static const Difficulty	DEFAULT_DIFFICULTY = EASY;

public:
  Scenario(unsigned short height = DEFAULT_HEIGHT, unsigned short width = DEFAULT_WIDTH,
	   float speed = DEFAULT_SPEED, Difficulty difficulty = DEFAULT_DIFFICULTY);
  ~Scenario();

  Scenario(const Scenario &src);
  Scenario	&operator=(const Scenario &src);

public:
  void				addPlayer(const Player &p);
  const std::vector<Player>	&getPlayers() const;

  void				getMapSize(unsigned short &height, unsigned short &width);
  void				setMapSize(unsigned short height, unsigned short width);
  void				setGameSpeed(float speed);
  float				getGameSpeed() const;
  void				setDifficulty(Difficulty difficulty);
  Difficulty			getDifficulty() const;


private:
  std::vector<Player>	_players;

  struct
  {
    unsigned short	height;
    unsigned short	width;
  }			_map;

  struct
  {
    float	speed;
    Difficulty	difficulty;
  }		_game;
};