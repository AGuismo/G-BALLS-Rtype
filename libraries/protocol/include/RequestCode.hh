#ifndef REQUESTCODE_H_
# define REQUESTCODE_H_

# include	"types.hh"

namespace requestCode
{
  namespace server
  {
    static const CodeID OK =			1000;
    static const CodeID BAD_REQ =		1001;
    static const CodeID FORBIDDEN =		1002;
    static const CodeID NOT_IMPLEMENTED =	1003;
    static const CodeID NO_CONTENT =		1004;
    static const CodeID PARTIAL_CONTENT =	1005;
    static const CodeID NO_SLOTS =		1006;
  }

  namespace auth
  {
    static const CodeID CONNECT =		100;
    static const CodeID CHANGE_PASSWD =		101;
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
    static const CodeID LIST =			300;
    static const CodeID CREAT =			301;
    static const CodeID JOIN =			302;
    static const CodeID CANCEL =		303;
    static const CodeID CLI_START =		304;

    static const CodeID UPDATE =		1300;
    static const CodeID STOPPED =		1301;
    static const CodeID SERV_START =	1302;

    static const Ruint8	PASS =			1;
    static const Ruint8	NO_PASS =		0;

    static const Status OUT_GAME =		0;
    static const Status IN_GAME =		1;
    static const Status CANCELED =		2;
    static const Status FINISHED =		3;
    static const Status UPDATE_GAME =		4;
  }

  namespace root
  {
    static const CodeID SHUTDOWN =		400;
  };

  namespace game
  {
    static const CodeID LEAVE =			606;
    static const CodeID ALIVE =			607;

    static const CodeID ELEM =			1600;
    static const CodeID DEATH =			1601;
    static const CodeID BUFF =			1602;
    static const CodeID SCORE =			1603;
    static const CodeID VICTORY =		1604;
    static const CodeID LOOSE =			1605;
    static const CodeID NEXTSTAGE =		1606;
    namespace client
    {
      static const ::game::Event	MOVE =		0;
      static const ::game::Event	SHOOT =		1;

      static const ::game::Dir	NORTH =			0;
      static const ::game::Dir	NORTH_EAST =		1;
      static const ::game::Dir	EAST =			2;
      static const ::game::Dir	SOUTH_EAST =		3;
      static const ::game::Dir	SOUTH =			4;
      static const ::game::Dir	SOUTH_WEST =		5;
      static const ::game::Dir	WEST =			6;
      static const ::game::Dir	NORTH_WEST =		7;

      static const ::game::Shoot	SIMPLE =	0;
      static const ::game::Shoot	BLAST =		1;
    }

    namespace server
    {
      static const ::game::Type PLAYER1 =		0;
      static const ::game::Type PLAYER2 =		1;
      static const ::game::Type PLAYER3 =		2;
      static const ::game::Type PLAYER4 =		3;
      static const ::game::Type SBYDOS1 =		4;
      static const ::game::Type SLIDER =		5;
      static const ::game::Type ZOGZOG =		6;
      static const ::game::Type SHRIMP_BOSS =		7;
      static const ::game::Type GARBAGE_BOSS =		8;
      static const ::game::Type PLAYER_LASER =		9;
      static const ::game::Type PLAYER_BLAST =		10;
      static const ::game::Type BYDOS_PLASMA =		11;
      static const ::game::Type BYDOS_LASER =		12;
      static const ::game::Type DESTRUCTIBLE_WALL =	13;
      static const ::game::Type INDESTRUCTIBLE_WALL =	14;
      static const ::game::Type BG1 =			15;
      static const ::game::Type BG2 =			16;
      static const ::game::Type VICTORY =		17;
      static const ::game::Type LOOSE =			18;
      static const ::game::Type NEXSTAGE =		19;
      static const ::game::Type COMET =			20;
      static const ::game::Type NORMAL_BANG =		21;
      static const ::game::Type BIG_BANG =		22;
      static const ::game::Type VITALITY_BONUS =	23;
      static const ::game::Type POWER_BONUS =		24;
      static const ::game::Type MISSILE =		25;
      static const ::game::Type IA =			26;
      static const ::game::Type BOSS =			27;
      static const ::game::Type PLAYER =		28;
      static const ::game::Type BONUS =			29;
    }
  }
}

#endif /* REQUESTCODE_H_ */
