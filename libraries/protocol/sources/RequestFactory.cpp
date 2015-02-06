#include	<typeinfo>
#include	"RequestFactory.hh"
#include	"Protocol.hpp"
#include	"ARequest.hh"
#include	"AuthRequest.hh"
#include	"SessionRequest.hh"
#include	"ServerRequest.hh"
#include	"PartyRequest.hh"
#include	"RootRequest.hh"
#include	"AliveRequest.hh"
// #include	"BuffRequest.hh"
#include	"DeathRequest.hh"
#include	"ElemRequest.hh"
#include	"LeaveRequest.hh"
#include	"LooseRequest.hh"
#include	"VictoryRequest.hh"
// #include	"ScoreRequest.hh"
#include	"ChatSendRequest.hh"
#include	"ChatRecvRequest.hh"

namespace	request
{

  Factory::Factory()
  {
    _lnk[rtype::protocol::requestCode::auth::CONNECT] = new Auth::Connect;
    _lnk[rtype::protocol::requestCode::auth::CHANGE_PASSWD] = new Auth::ChangePass;
    _lnk[rtype::protocol::requestCode::auth::NEW_USER] = new Auth::NewUser;
    _lnk[rtype::protocol::requestCode::auth::SESSION] = new SessionRequest;

    _lnk[rtype::protocol::requestCode::party::LIST] = new Party::List;
    _lnk[rtype::protocol::requestCode::party::CREAT] = new Party::Create;
    _lnk[rtype::protocol::requestCode::party::JOIN] = new Party::Join;
    _lnk[rtype::protocol::requestCode::party::CANCEL] = new Party::Cancel;
    _lnk[rtype::protocol::requestCode::party::CLI_START] = new Party::Start;

    _lnk[rtype::protocol::requestCode::party::UPDATE] = new Party::Update;
    _lnk[rtype::protocol::requestCode::party::STOPPED] = new Party::Stopped;
    _lnk[rtype::protocol::requestCode::party::SERV_START] = new Party::Launch;

    _lnk[rtype::protocol::requestCode::server::OK] = new ServerRequest;
    _lnk[rtype::protocol::requestCode::server::BAD_REQ] = new ServerRequest;
    _lnk[rtype::protocol::requestCode::server::FORBIDDEN] = new ServerRequest;
    _lnk[rtype::protocol::requestCode::server::NOT_IMPLEMENTED] = new ServerRequest;
    _lnk[rtype::protocol::requestCode::server::NO_CONTENT] = new ServerRequest;
    _lnk[rtype::protocol::requestCode::server::PARTIAL_CONTENT] = new ServerRequest;
    _lnk[rtype::protocol::requestCode::server::NO_SLOTS] = new ServerRequest;

    _lnk[rtype::protocol::requestCode::game::ALIVE] = new AliveRequest;
    // _lnk[rtype::protocol::requestCode::game::BUFF] = new BuffRequest;
    _lnk[rtype::protocol::requestCode::game::DEATH] = new DeathRequest;
    _lnk[rtype::protocol::requestCode::game::ELEM] = new ElemRequest;
    _lnk[rtype::protocol::requestCode::game::LEAVE] = new LeaveRequest;
    _lnk[rtype::protocol::requestCode::game::LOOSE] = new LooseRequest;
    // _lnk[rtype::protocol::requestCode::game::SCORE] = new ScoreRequest;
    _lnk[rtype::protocol::requestCode::game::VICTORY] = new VictoryRequest;

    _lnk[rtype::protocol::requestCode::chat::RECV_MSG] = new ChatRecvRequest;
    _lnk[rtype::protocol::requestCode::chat::SEND_MSG] = new ChatSendRequest;

    _lnk[rtype::protocol::requestCode::root::SHUTDOWN] = new root::Shutdown;
  }

  Factory::~Factory()
  {
    while (!_lnk.empty())
    {
      delete _lnk.begin()->second;
      _lnk.erase(_lnk.begin());
    }
  }

  Factory	&Factory::getInstance()
  {
    static Factory	f;

    return (f);
  }

  ARequest		*Factory::factory(Protocol &p, const rtype::protocol::CodeID code)
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
