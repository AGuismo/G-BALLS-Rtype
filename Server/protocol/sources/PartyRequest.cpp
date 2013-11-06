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

  // Server Responses

  Launch::Launch() :
    ARequest(requestCode::party::SERV_START), _id(0)
  {

  }

  Launch::Launch(requestCode::PartyID id) :
    ARequest(requestCode::party::SERV_START), _id(id)
  {

  }

  Launch::~Launch()
  {

  }

  Launch::Launch(const Launch &src) :
    ARequest(src), _id(src._id)
  {

  }

  Launch		&Launch::operator=(Launch const &src)
  {
    if (&src != this)
      {
	_code = src._code;
	_id = src._id;
      }
    return (*this);
  }

  requestCode::PartyID		Launch::PartyID() const
  {
    return (_id);
  }

  void				Launch::PartyID(requestCode::PartyID id)
  {
    _id = id;
  }

  Protocol			&Launch::Megan_serialize(Protocol &rhs) const
  {
    rhs << _code;
    return (rhs);
  }

  Protocol			&Launch::Fox_unserialize(Protocol &rhs)
  {
    return (rhs);
  }

  ARequest			*Launch::clone()
  {
    return (new Launch());
  }

  requestCode::PartyID		Launch::Unique()
  {
    static requestCode::PartyID	id = 0;

    return (++id);
  }

}
