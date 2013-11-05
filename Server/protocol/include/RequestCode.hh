#ifndef REQUESTCODE_H_
# define REQUESTCODE_H_

# include	"types.hh"

namespace requestCode
{
  typedef Ruint16	CodeID;
  typedef Ruint32	PasswordType;
  typedef Ruint16	UsernameLen;
  typedef Ruint16	SessionID;

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

    static const CodeID NEW =			1300;
    static const CodeID UPDATE =		1301;
    static const CodeID END =			1302;
    static const CodeID SERV_START =		1303;
  }

  namespace game
  {
    static const CodeID MOVE_LEFT =		600;
    static const CodeID MOVE_RIGHT =		601;
    static const CodeID MOVE_UP =		602;
    static const CodeID MOVE_DOWN =		603;
    static const CodeID MOVE_LEFT_UP =		604;
    static const CodeID MOVE_LEFT_DOWN =	605;
    static const CodeID MOVE_RIGHT_UP =		606;
    static const CodeID MOVE_RIGHT_DOWN =	607;
    static const CodeID ATTACK_FIRST =		608;
    static const CodeID ATTACK_SECOND =		609;
    static const CodeID LEAVE =			610;
    static const CodeID ALIVE =			611;

    static const CodeID ELEM =			1600;
    static const CodeID DEATH =			1601;
    static const CodeID BUFF =			1602;
    static const CodeID SCORE =			1603;
    static const CodeID VICTORY =		1604;
    static const CodeID LOOSE =			1605;
  }
}

#endif /* REQUESTCODE_H_ */
