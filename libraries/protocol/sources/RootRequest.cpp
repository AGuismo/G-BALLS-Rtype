#include	"RootRequest.hh"
#include	"Protocol.hpp"

namespace	root
{
  Shutdown::Shutdown() :
    ARequest(rtype::protocol::requestCode::root::SHUTDOWN)
  {

  }

  Shutdown::~Shutdown()
  {

  }

  Shutdown::Shutdown(const Shutdown &src) :
    ARequest(src)
  {

  }

  Shutdown		&Shutdown::operator=(Shutdown const &src)
  {
    if (&src != this)
      {
	_code = src._code;
      }
    return (*this);
  }

  Protocol			&Shutdown::serialize(Protocol &rhs) const
  {
    rhs << _code;
    return (rhs);
  }

  Protocol			&Shutdown::unserialize(Protocol &rhs)
  {
    return (rhs);
  }

  ARequest			*Shutdown::clone() const
  {
    return (new Shutdown());
  }
}
