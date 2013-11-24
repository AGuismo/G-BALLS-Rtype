#include	<typeinfo>
#include	"RequestFactory.hh"
#include	"Protocol.hpp"
#include	"ARequest.hh"
#include	"AuthRequest.hh"
#include	"SessionRequest.hh"
#include	"ServerRequest.hh"
#include	"PartyRequest.hh"
#include	"RootRequest.hh"
#include	"AliveRequest.h"
#include	"BuffRequest.h"
#include	"DeathRequest.h"
#include	"ElemRequest.hh"
#include	"LeaveRequest.h"
#include	"LooseRequest.h"
#include	"VictoryRequest.h"
#include	"EventRequest.hh"
#include	"ScoreRequest.h"
#include	"ChatSendRequest.h"
#include	"ChatRecvRequest.h"

namespace	request
{

  Factory::Factory()
  {
    _lnk[requestCode::auth::CONNECT] = new Auth::Connect;
    _lnk[requestCode::auth::CHANGE_PASSWD] = new Auth::ChangePass;
    _lnk[requestCode::auth::NEW_USER] = new Auth::NewUser;
    _lnk[requestCode::auth::SESSION] = new SessionRequest;

    _lnk[requestCode::party::LIST] = new Party::List;
    _lnk[requestCode::party::CREAT] = new Party::Create;
    _lnk[requestCode::party::JOIN] = new Party::Join;
    _lnk[requestCode::party::CANCEL] = new Party::Cancel;
    _lnk[requestCode::party::SERV_START] = new Party::Launch;
    _lnk[requestCode::party::UPDATE] = new Party::Update;
    _lnk[requestCode::party::CLI_START] = new Party::Start;

    _lnk[requestCode::server::OK] = new ServerRequest;
    _lnk[requestCode::server::BAD_REQ] = new ServerRequest;
    _lnk[requestCode::server::FORBIDDEN] = new ServerRequest;
    _lnk[requestCode::server::NOT_IMPLEMENTED] = new ServerRequest;
    _lnk[requestCode::server::NO_CONTENT] = new ServerRequest;
    _lnk[requestCode::server::PARTIAL_CONTENT] = new ServerRequest;
    _lnk[requestCode::server::NO_SLOTS] = new ServerRequest;

	_lnk[requestCode::game::ALIVE] = new AliveRequest;
	_lnk[requestCode::game::BUFF] = new BuffRequest;
	_lnk[requestCode::game::DEATH] = new DeathRequest;
	_lnk[requestCode::game::ELEM] = new ElemRequest;
	_lnk[requestCode::game::EVENT] = new EventRequest;
	_lnk[requestCode::game::LEAVE] = new LeaveRequest;
	_lnk[requestCode::game::LOOSE] = new LooseRequest;
	_lnk[requestCode::game::SCORE] = new ScoreRequest;
	_lnk[requestCode::game::VICTORY] = new VictoryRequest;

	_lnk[requestCode::chat::RECV_MSG] = new ChatRecvRequest;
	_lnk[requestCode::chat::SEND_MSG] = new ChatSendRequest;

    _lnk[requestCode::root::SHUTDOWN] = new root::Shutdown;
  }

  Factory::~Factory()
  {

  }

  Factory	&Factory::getInstance()
  {
    static Factory	f;

    return (f);
  }

  ARequest		*Factory::factory(Protocol &p, const requestCode::CodeID code)
  {
    Factory		&f = Factory::getInstance();
    lnk_type::iterator	it;
    ARequest		*req;

    if ((it = f._lnk.find(code)) == f._lnk.end())
      throw ARequest::Exception("Invalid Code");
    req = it->second->clone();
    req->unserialize(p);
    return (req);
  }

  void			Factory::factory(Protocol &p, const ARequest &output)
  {
    output.serialize(p);
  }

}
