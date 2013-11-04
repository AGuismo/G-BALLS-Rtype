#include	<typeinfo>
#include	"RequestFactory.hh"
#include	"Protocol.hpp"
#include	"ARequest.hh"
#include	"AuthRequest.hh"

namespace	request
{

  Factory::Factory()
  {
    _lnk[requestCode::auth::CONNECT] = new Auth::Connect;
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
