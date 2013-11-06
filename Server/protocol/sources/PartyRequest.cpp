#include	"PartyRequest.hh"
#include	"Protocol.hpp"

namespace	Party
{
  Start::Start() :
    ARequest(requestCode::party::CLI_START)
  {

  }

  Start::~Start()
  {

  }

  Start::Start(const Start &src) :
    ARequest(src)
  {

  }

  Start		&Start::operator=(Start const &src)
  {
    if (&src != this)
      {
	_code = src._code;
      }
    return (*this);
  }

  Protocol			&Start::Megan_serialize(Protocol &rhs) const
  {
    rhs << _code;
    return (rhs);
  }

  Protocol			&Start::Fox_unserialize(Protocol &rhs)
  {
    return (rhs);
  }

  ARequest			*Start::clone()
  {
    return (new Start());
  }

}
