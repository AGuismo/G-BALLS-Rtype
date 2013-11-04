#include	"RequestFactory.hh"
#include	"Protocol.hpp"
#include	"ARequest.hh"

namespace	request
{

  Factory::Factory()
  {

  }

  Factory::~Factory()
  {

  }

  Factory	&Factory::getInstance()
  {
    static Factory	f;

    return (f);
  }

  const ARequest	Factory::factory(Protocol &p, const requestCode::CodeID code)
  {
    Factory		&f = Factory::getInstance();

    (void)f;
    (void)p;
    (void)code;
    // .Megan_serialize(*this);
    return (ARequest(requestCode::auth::CONNECT));
  }

  void			Factory::factory(Protocol &p, const ARequest &output)
  {
    Factory		&f = Factory::getInstance();

    (void)p;
    (void)output;
    (void)f;
    // output.Fox_unserialize(p);
  }

}
