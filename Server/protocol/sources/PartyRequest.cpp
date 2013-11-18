#include	"PartyRequest.hh"
#include	"Protocol.hpp"

namespace	Party
{
  ///////////
  // Start //
  ///////////

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

  Protocol			&Start::serialize(Protocol &rhs) const
  {
    rhs << _code;
    return (rhs);
  }

  Protocol			&Start::unserialize(Protocol &rhs)
  {
    return (rhs);
  }

  ARequest			*Start::clone()
  {
    return (new Start());
  }

  //////////
  // List //
  //////////
  List::List() :
    ARequest(requestCode::party::LIST)
  {

  }

  List::~List()
  {

  }

  List::List(const List &src) :
    ARequest(src)
  {

  }

  List		&List::operator=(List const &src)
  {
    if (&src != this)
      {
	_code = src._code;
      }
    return (*this);
  }

  Protocol			&List::serialize(Protocol &rhs) const
  {
    rhs << _code;
    return (rhs);
  }

  Protocol			&List::unserialize(Protocol &rhs)
  {
    return (rhs);
  }

  ARequest			*List::clone()
  {
    return (new List());
  }

  ////////////
  // Create //
  ////////////
  Create::Create() :
    ARequest(requestCode::party::CREAT)
  {

  }

  Create::Create(const std::string &partyName, Ruint8 nbPlayers) :
    ARequest(requestCode::party::CREAT), _partyName(partyName), _maxPlayers(nbPlayers)
  {

  }

  Create::Create(const std::string &partyName, Ruint8 nbPlayers, requestCode::PasswordType pass) :
    ARequest(requestCode::party::CREAT), _partyName(partyName), _maxPlayers(nbPlayers),
    _isPassword(true), _partyPass(pass)
  {

  }

  Create::~Create()
  {

  }

  Create::Create(const Create &src) :
    ARequest(src)
  {

  }

  Create		&Create::operator=(Create const &src)
  {
    if (&src != this)
      {
	_code = src._code;
      }
    return (*this);
  }

  Protocol			&Create::serialize(Protocol &rhs) const
  {
    rhs << _code;
    return (rhs);
  }

  Protocol			&Create::unserialize(Protocol &rhs)
  {
    return (rhs);
  }

  ARequest			*Create::clone()
  {
    return (new Create());
  }

  ////////////
  // Cancel //
  ////////////
  Cancel::Cancel() :
    ARequest(requestCode::party::CANCEL)
  {

  }

  Cancel::~Cancel()
  {

  }

  Cancel::Cancel(const Cancel &src) :
    ARequest(src)
  {

  }

  Cancel		&Cancel::operator=(Cancel const &src)
  {
    if (&src != this)
      {
	_code = src._code;
      }
    return (*this);
  }

  Protocol			&Cancel::serialize(Protocol &rhs) const
  {
    rhs << _code;
    return (rhs);
  }

  Protocol			&Cancel::unserialize(Protocol &rhs)
  {
    return (rhs);
  }

  ARequest			*Cancel::clone()
  {
    return (new Cancel());
  }

  //////////
  // Join //
  //////////
  Join::Join():
    ARequest(requestCode::party::JOIN)
  {

  }

  Join::Join(const std::string &partyName, Ruint8 nbPlayers) :
    ARequest(requestCode::party::JOIN), _partyName(partyName), _maxPlayers(nbPlayers)
  {

  }

  Join::Join(const std::string &partyName, Ruint8 nbPlayers, requestCode::PasswordType pass) :
    ARequest(requestCode::party::JOIN), _partyName(partyName), _maxPlayers(nbPlayers),
    _isPassword(true), _partyPass(pass)
  {

  }

  Join::~Join()
  {

  }

  Join::Join(const Join &src) :
    ARequest(src)
  {

  }

  Join		&Join::operator=(Join const &src)
  {
    if (&src != this)
      {
	_code = src._code;
      }
    return (*this);
  }

  Protocol			&Join::serialize(Protocol &rhs) const
  {
    rhs << _code;
    return (rhs);
  }

  Protocol			&Join::unserialize(Protocol &rhs)
  {
    return (rhs);
  }

  ARequest			*Join::clone()
  {
    return (new Join());
  }

  //////////////////////
  // Server Responses //
  //////////////////////

  ////////////
  // Launch //
  ////////////
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

  Protocol			&Launch::serialize(Protocol &rhs) const
  {
    rhs << _code;
    return (rhs);
  }

  Protocol			&Launch::unserialize(Protocol &rhs)
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

  ////////////
  // Update //
  ////////////
  Update::Update() :
    ARequest(requestCode::party::UPDATE)
  {

  }

  Update::Update(const std::string &partyName, Ruint8 availableSlots, Ruint8 maxPlayers,
		 Ruint8 partyPass, Ruint8 status) :
    ARequest(requestCode::party::UPDATE), _partyName(partyName), _availableSlots(availableSlots),
    _maxPlayers(maxPlayers), _isPassword(partyPass), _status(status)
  {

  }

  Update::~Update()
  {

  }

  Update::Update(const Update &src) :
    ARequest(src), _partyName(src._partyName), _availableSlots(src._availableSlots),
    _maxPlayers(src._maxPlayers), _isPassword(src._isPassword), _status(src._status)
  {

  }

  Update		&Update::operator=(Update const &src)
  {
    if (&src != this)
      {
	_code = src._code;
	_partyName = src._partyName;
	_availableSlots = src._availableSlots;
	_maxPlayers = src._maxPlayers;
	_isPassword = src._isPassword;
	_status = src._status;
      }
    return (*this);
  }

  Protocol			&Update::serialize(Protocol &rhs) const
  {
    requestCode::PartynameLen	len = _partyName.length();

    rhs << _code << len;
    rhs.push(_partyName, len);
    rhs << _availableSlots << _maxPlayers << _isPassword << _status;
    return (rhs);
  }

  Protocol			&Update::unserialize(Protocol &rhs)
  {
    requestCode::PartynameLen	len;

    rhs >> len;
    rhs.pop(_partyName, len);
    rhs >> _availableSlots >> _maxPlayers >> _isPassword >> _status;
    return (rhs);
  }

  ARequest			*Update::clone()
  {
    return (new Update());
  }

}
