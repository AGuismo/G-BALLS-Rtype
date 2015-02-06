#ifndef REQUESTCODE_H_
# define REQUESTCODE_H_

# include	"ProtocolTypes.hh"

namespace	rtype
{
  namespace	protocol
  {
    namespace	requestCode
    {
      namespace server
      {
	static const rtype::protocol::CodeID OK =			1000;
	static const rtype::protocol::CodeID BAD_REQ =		1001;
	static const rtype::protocol::CodeID FORBIDDEN =		1002;
	static const rtype::protocol::CodeID NOT_IMPLEMENTED =	1003;
	static const rtype::protocol::CodeID NO_CONTENT =		1004;
	static const rtype::protocol::CodeID PARTIAL_CONTENT =	1005;
	static const rtype::protocol::CodeID NO_SLOTS =		1006;
      } // !server

      namespace auth
      {
	static const rtype::protocol::CodeID CONNECT =		100;
	static const rtype::protocol::CodeID CHANGE_PASSWD =		101;
	static const rtype::protocol::CodeID NEW_USER =		102;
	static const rtype::protocol::CodeID SESSION =		1100;
      } // !auth

      namespace chat
      {
	static const rtype::protocol::CodeID SEND_MSG =		200;

	static const rtype::protocol::CodeID RECV_MSG =		1200;
      } // !chat

      namespace party
      {
	static const rtype::protocol::CodeID LIST =			300;
	static const rtype::protocol::CodeID CREAT =			301;
	static const rtype::protocol::CodeID JOIN =			302;
	static const rtype::protocol::CodeID CANCEL =		303;
	static const rtype::protocol::CodeID CLI_START =		304;

	static const rtype::protocol::CodeID UPDATE =		1300;
	static const rtype::protocol::CodeID STOPPED =		1301;
	static const rtype::protocol::CodeID SERV_START =	1302;

	static const rtype::protocol::Ruint8	PASS =			1;
	static const rtype::protocol::Ruint8	NO_PASS =		0;

	static const rtype::protocol::Status OUT_GAME =		0;
	static const rtype::protocol::Status IN_GAME =		1;
	static const rtype::protocol::Status CANCELED =		2;
	static const rtype::protocol::Status FINISHED =		3;
	static const rtype::protocol::Status UPDATE_GAME =		4;
      } // !party

      namespace root
      {
	static const rtype::protocol::CodeID SHUTDOWN =		400;
      }; // !root

      namespace game
      {
	static const rtype::protocol::CodeID LEAVE =			606;
	static const rtype::protocol::CodeID ALIVE =			607;

	static const rtype::protocol::CodeID ELEM =			1600;
	static const rtype::protocol::CodeID DEATH =			1601;
	static const rtype::protocol::CodeID BUFF =			1602;
	// static const rtype::protocol::CodeID SCORE =			1603;
	static const rtype::protocol::CodeID VICTORY =		1604;
	static const rtype::protocol::CodeID LOOSE =			1605;
	// static const rtype::protocol::CodeID NEXTSTAGE =		1606;
	// namespace client
	// {
	//   static const rtype::protocol::game::Event	MOVE =		0;
	//   static const rtype::protocol::game::Event	SHOOT =		1;

	//   static const rtype::protocol::game::Dir	NORTH =			0;
	//   static const rtype::protocol::game::Dir	NORTH_EAST =		1;
	//   static const rtype::protocol::game::Dir	EAST =			2;
	//   static const rtype::protocol::game::Dir	SOUTH_EAST =		3;
	//   static const rtype::protocol::game::Dir	SOUTH =			4;
	//   static const rtype::protocol::game::Dir	SOUTH_WEST =		5;
	//   static const rtype::protocol::game::Dir	WEST =			6;
	//   static const rtype::protocol::game::Dir	NORTH_WEST =		7;

	//   static const rtype::protocol::game::Shoot	SIMPLE =	0;
	//   static const rtype::protocol::game::Shoot	BLAST =		1;
	// } // !client

	// namespace server
	// {
	//   static const rtype::protocol::Type PLAYER1 =		0;
	//   static const rtype::protocol::Type PLAYER2 =		1;
	//   static const rtype::protocol::Type PLAYER3 =		2;
	//   static const rtype::protocol::Type PLAYER4 =		3;
	//   static const rtype::protocol::Type SBYDOS1 =		4;
	//   static const rtype::protocol::Type SLIDER =		5;
	//   static const rtype::protocol::Type ZOGZOG =		6;
	//   static const rtype::protocol::Type SHRIMP_BOSS =		7;
	//   static const rtype::protocol::Type GARBAGE_BOSS =		8;
	//   static const rtype::protocol::Type PLAYER_LASER =		9;
	//   static const rtype::protocol::Type PLAYER_BLAST =		10;
	//   static const rtype::protocol::Type BYDOS_PLASMA =		11;
	//   static const rtype::protocol::Type BYDOS_LASER =		12;
	//   static const rtype::protocol::Type DESTRUCTIBLE_WALL =	13;
	//   static const rtype::protocol::Type INDESTRUCTIBLE_WALL =	14;
	//   static const rtype::protocol::Type BG1 =			15;
	//   static const rtype::protocol::Type BG2 =			16;
	//   static const rtype::protocol::Type VICTORY =		17;
	//   static const rtype::protocol::Type LOOSE =			18;
	//   static const rtype::protocol::Type NEXSTAGE =		19;
	//   static const rtype::protocol::Type COMET =			20;
	//   static const rtype::protocol::Type NORMAL_BANG =		21;
	//   static const rtype::protocol::Type BIG_BANG =		22;
	//   static const rtype::protocol::Type VITALITY_BONUS =	23;
	//   static const rtype::protocol::Type POWER_BONUS =		24;
	//   static const rtype::protocol::Type MISSILE =		25;
	//   static const rtype::protocol::Type IA =			26;
	//   static const rtype::protocol::Type BOSS =			27;
	//   static const rtype::protocol::Type PLAYER =		28;
	//   static const rtype::protocol::Type BONUS =			29;
	// }
      } // !game
    } // !requestCode
  } // !protocol
} // !rtype
#endif /* REQUESTCODE_H_ */
