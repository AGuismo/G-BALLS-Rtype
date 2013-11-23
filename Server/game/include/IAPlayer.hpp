#ifndef IAPLAYER_H_
# define IAPLAYER_H_

#include	"types.h"

struct		IAPlayer
{
  typedef unsigned int	size_type;

  static const int	PLAYER1 = 0;
  static const int	PLAYER2 = 1;
  static const int	PLAYER3 = 2;
  static const int	PLAYER4 = 3;

  static const int	MAX_PLAYERS = 4;

  union
  {
    struct	Players
    {
      game::Pos	first;
      game::Pos	second;
      game::Pos	third;
      game::Pos	fourth;
    }		player;
    game::Pos	players[MAX_PLAYERS];
  }		player;
  size_type	size;

  game::Pos	&operator[](const int pos)
  {
    return (player.players[pos]);
  }
};

// IAPlayer::Players	players = ia.player.player;
// game::Pos		player = ia[PLAYER_X];
// game::Pos		player = ia.player.player.first;

// ia[PLAYER_X] = x;

#endif /* IAPLAYER_H_ */
