#ifndef REQUESTCODE_H_
# define REQUESTCODE_H_

# include	"types.hh"

namespace requestCode
{
  namespace server
  {
    static const CodeID OK =		1000;
    static const CodeID BAD_REQ =		1001;
    static const CodeID FORBIDDEN =		1002;
    static const CodeID NOT_IMPLEMENTED =	1003;
    static const CodeID NO_CONTENT =	1004;
    static const CodeID PARTIAL_CONTENT =	1005;
    static const CodeID NO_SLOTS =		1006;
  }

  namespace auth
  {
    static const CodeID CONNECT =		100;
    static const CodeID CHANGE_PASSWD =	101;
    static const CodeID NEW_USER =		102;
    static const CodeID SESSION =		1100;
  }

  namespace chat
  {
    static const CodeID SEND_MSG =		200;

    static const CodeID RECV_MSG =		1200;
  }

  namespace party
  {
    static const CodeID LIST =		300;
    static const CodeID CREAT =		301;
    static const CodeID JOIN =		302;
    static const CodeID CANCEL =		303;
    static const CodeID CLI_START =		304;

    static const CodeID UPDATE =		1300;
    static const CodeID STOPPED =		1301;
    static const CodeID SERV_START =	1302;

    static const Status OUT_GAME =		0;
    static const Status IN_GAME =		1;
    static const Status CANCELED =		2;
    static const Status FINISHED =		3;
    static const Status UPDATE_GAME =	4;
  }

  namespace root
  {
    static const CodeID SHUTDOWN =		400;
  };

  namespace game
  {
    static const CodeID EVENT =		600;
    static const CodeID LEAVE =		606;
    static const CodeID ALIVE =		607;

    static const CodeID ELEM =			1600;
    static const CodeID DEATH =			1601;
    static const CodeID BUFF =			1602;
    static const CodeID SCORE =			1603;
    static const CodeID VICTORY =		1604;
    static const CodeID LOOSE =			1605;
    static const CodeID NEXTSTAGE =		1606;
    namespace client
    {
      using ::game::Event;
      using ::game::Dir;
      using ::game::Shoot;


      static const Event	MOVE =		0;
      static const Event	SHOOT =		1;

      static const Dir	NORTH =			0;
      static const Dir	NORTH_EAST =	1;
      static const Dir	EAST =			2;
      static const Dir	SOUTH_EAST =	3;
      static const Dir	SOUTH =			4;
      static const Dir	SOUTH_WEST =	5;
      static const Dir	WEST =			6;
      static const Dir	NORTH_WEST =	7;

      static const Shoot	SIMPLE =	0;
      static const Shoot	BLAST =		1;
    }

    namespace server
    {
      using ::game::Type;

      static const Type PLAYER1 = 0;
      static const Type PLAYER2 = 1;
      static const Type PLAYER3 = 2;
      static const Type PLAYER4 = 3;
      static const Type SBYDOS1 = 4;
      static const Type SLIDER = 5;
      static const Type ZOGZOG = 6;
      static const Type SHRIMP_BOSS = 7;
      static const Type GARBAGE_BOSS = 8;
      static const Type PLAYER_LASER = 9;
      static const Type PLAYER_BLAST = 10;
      static const Type BYDOS_PLASMA = 11;
      static const Type BYDOS_LASER = 12;
	  static const Type DESTRUCTIBLE_WALL = 13;
	  static const Type INDESTRUCTIBLE_WALL = 14;
      static const Type BG1 = 15;
      static const Type BG2 = 16;
      static const Type VICTORY = 17;
      static const Type LOOSE = 18;
      static const Type NEXSTAGE = 19;
      static const Type COMET = 20;
      static const Type NORMAL_BANG = 21;
      static const Type BIG_BANG = 22;
	  static const Type VITALITY_BONUS = 23;
	  static const Type POWER_BONUS = 24;
	  static const Type MISSILE = 25;
	  static const Type IA = 26;
	  static const Type BOSS = 27;
	  static const Type PLAYER = 28;
	  static const Type BONUS = 29;
    }
  }
}

#endif /* REQUESTCODE_H_ */
