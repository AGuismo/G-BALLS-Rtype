#include	<typeinfo>
#include	"RequestFactory.hh"
#include	"Protocol.hpp"
#include	"ARequest.hh"
#include	"AuthRequest.hh"
#include	"ServerRequest.hh"

namespace	request
{

  Factory::Factory()
  {
    _lnk[requestCode::auth::CONNECT] = new Auth::Connect;
    _lnk[requestCode::auth::CHANGE_PASSWD] = new Auth::ChangePass;

    _lnk[requestCode::server::OK] = new ServerRequest;
    _lnk[requestCode::server::BAD_REQ] = new ServerRequest;
    _lnk[requestCode::server::FORBIDDEN] = new ServerRequest;
    _lnk[requestCode::server::NOT_IMPLEMENTED] = new ServerRequest;
    _lnk[requestCode::server::NO_CONTENT] = new ServerRequest;
    _lnk[requestCode::server::PARTIAL_CONTENT] = new ServerRequest;
    _lnk[requestCode::server::NO_SLOTS] = new ServerRequest;
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

#if defined(DEBUG)
    if ((it = f._lnk.find(code)) == f._lnk.end())
      throw ARequest::Exception("Invalid Code");
#endif

    ARequest		*req = f._lnk.find(code)->second->clone();
    req->Fox_unserialize(p);
    return (req);
  }

  void			Factory::factory(Protocol &p, const ARequest &output)
  {
    output.Megan_serialize(p);
  }

}