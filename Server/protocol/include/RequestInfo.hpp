#ifndef REQUESTINFO_H_
# define REQUESTINFO_H_

# include	<map>
# include	"RequestCode.hh"
# include	"PartyRequest.hh"
# include	"AuthRequest.hh"
# include	"RootRequest.hh"
# include	"SessionRequest.hh"
# include	"ElemRequest.hh"
# include	"ServerRequest.hh"
# include	"EventRequest.hh"
# include	"AliveRequest.h"
# include	"VictoryRequest.h"
# include	"BuffRequest.h"
# include	"ScoreRequest.h"
# include	"DeathRequest.h"
# include	"LeaveRequest.h"
# include	"LooseRequest.h"

struct	detail
{
  static const char	*AUTH_CONNECT;
  static const char	*AUTH_NEWUSER;
  static const char	*AUTH_CHANGEPASS;
  static const char	*SESSION;

  static const char	*GAME_BUFF;
  static const char	*GAME_ALIVE;
  static const char	*GAME_DEATH;
  static const char	*GAME_ELEM;
  static const char	*GAME_EVENT;
  static const char	*GAME_LEAVE;
  static const char	*GAME_LOOSE;
  static const char	*GAME_VICTORY;

  static const char	*PARTY_START;
  static const char	*PARTY_LIST;
  static const char	*PARTY_CREATE;
  static const char	*PARTY_CANCEL;
  static const char	*PARTY_JOIN;
  static const char	*PARTY_LAUNCH;
  static const char	*PARTY_UPDATE;
  static const char	*PARTY_STOPPED;

  static const char	*ROOT_SHUTDOWN;

  static const char	*SCORE;

  static const char	*OK;
  static const char	*BAD_REQ;
  static const char	*FORBIDDEN;
  static const char	*NOT_IMPLEMENTED;
  static const char	*NO_CONTENT;
  static const char	*PARTIAL_CONTENT;
  static const char	*NO_SLOTS;
};

template <typename T> struct	Info;

template <> struct Info<Auth::Connect> {static const char * Detail() {return (detail::AUTH_CONNECT);}};
template <> struct Info<Auth::NewUser> {static const char * Detail() {return (detail::AUTH_NEWUSER);}};
template <> struct Info<Auth::ChangePass> {static const char * Detail() {return (detail::AUTH_CHANGEPASS);}};

template <> struct Info<SessionRequest> {static const char * Detail() {return (detail::SESSION);}};

template <> struct Info<BuffRequest> {static const char * Detail() {return (detail::GAME_BUFF);}};
template <> struct Info<AliveRequest> {static const char * Detail() {return (detail::GAME_ALIVE);}};
template <> struct Info<DeathRequest> {static const char * Detail() {return (detail::GAME_DEATH);}};
template <> struct Info<ElemRequest> {static const char * Detail() {return (detail::GAME_ELEM);}};
template <> struct Info<EventRequest> {static const char * Detail() {return (detail::GAME_EVENT);}};
template <> struct Info<LeaveRequest> {static const char * Detail() {return (detail::GAME_LEAVE);}};
template <> struct Info<LooseRequest> {static const char * Detail() {return (detail::GAME_LOOSE);}};
template <> struct Info<VictoryRequest> {static const char * Detail() {return (detail::GAME_VICTORY);}};

template <> struct Info<Party::Start> {static const char * Detail() {return (detail::PARTY_START);}};
template <> struct Info<Party::List> {static const char * Detail() {return (detail::PARTY_LIST);}};
template <> struct Info<Party::Create> {static const char * Detail() {return (detail::PARTY_CREATE);}};
template <> struct Info<Party::Cancel> {static const char * Detail() {return (detail::PARTY_CANCEL);}};
template <> struct Info<Party::Join> {static const char * Detail() {return (detail::PARTY_JOIN);}};
template <> struct Info<Party::Launch> {static const char * Detail() {return (detail::PARTY_LAUNCH);}};
template <> struct Info<Party::Update> {static const char * Detail() {return (detail::PARTY_UPDATE);}};
template <> struct Info<Party::Stopped> {static const char * Detail() {return (detail::PARTY_STOPPED);}};

template <> struct Info<root::Shutdown> {static const char * Detail() {return (detail::ROOT_SHUTDOWN);}};

template <> struct Info<ScoreRequest> {static const char * Detail() {return (detail::SCORE);}};

template <> struct Info<ServerRequest>
{
  static const char * Detail(const requestCode::CodeID id)
  {
    static std::map<requestCode::CodeID, const char *>	_map;

    if (_map.size() == 0)
      {
	_map[requestCode::server::OK] = detail::OK;
	_map[requestCode::server::BAD_REQ] = detail::BAD_REQ;
	_map[requestCode::server::FORBIDDEN] = detail::FORBIDDEN;
	_map[requestCode::server::NOT_IMPLEMENTED] = detail::NOT_IMPLEMENTED;
	_map[requestCode::server::NO_CONTENT] = detail::NO_CONTENT;
	_map[requestCode::server::PARTIAL_CONTENT] = detail::PARTIAL_CONTENT;
	_map[requestCode::server::NO_SLOTS] = detail::NO_SLOTS;
      }
    return (_map[id]);
  }
};

#endif /* REQUESTINFO_H_ */
