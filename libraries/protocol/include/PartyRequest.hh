#ifndef PARTYREQUEST_H_
# define PARTYREQUEST_H_

# include	"RequestCode.hh"
# include	"ARequest.hh"

namespace	Party
{
  // Client Asks

  struct	Start : public ARequest
  {
  public:
    Start();
    virtual ~Start();

  public:
    Start(const Start &);
    Start	&operator=(const Start &);

  public:
    Protocol			&serialize(Protocol &) const;
    Protocol			&unserialize(Protocol &);
    ARequest			*clone() const;
  };

  struct	List : public ARequest
  {
  public:
    List();
    virtual ~List();

  public:
    List(const List &);
    List	&operator=(const List &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone() const;
  };

  struct	Create : public ARequest
  {
  public:
    Create();
    Create(const std::string &partyName, rtype::protocol::Ruint8 nbPlayers);
    Create(const std::string &partyName, rtype::protocol::Ruint8 nbPlayers, rtype::protocol::PasswordType pass);
    virtual ~Create();

  public:
    Create(const Create &);
    Create	&operator=(const Create &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone() const;

  public:
    std::string			_partyName;
    rtype::protocol::Ruint8			_maxPlayers;
    rtype::protocol::Ruint8			_isPassword;
    rtype::protocol::PasswordType	_partyPass;
  };

  struct	Cancel : public ARequest
  {
  public:
    Cancel();
    virtual ~Cancel();

  public:
    Cancel(const Cancel &);
    Cancel	&operator=(const Cancel &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone() const;
  };

  struct	Join : public ARequest
  {
  public:
    Join(const std::string &partyName);
    Join(const std::string &partyName, rtype::protocol::PasswordType pass);
    Join();
    virtual ~Join();

  public:
    Join(const Join &);
    Join	&operator=(const Join &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone() const;

  public:
    std::string			_partyName;
    rtype::protocol::Ruint8			_maxPlayers;
    rtype::protocol::Ruint8			_isPassword;
    rtype::protocol::PasswordType	_partyPass;
  };


  //////////////////////
  // Server Responses //
  //////////////////////

  ////////////
  // Launch //
  ////////////
  struct	Launch : public ARequest
  {
  public:
    Launch();
    Launch(rtype::protocol::PartyID);
    virtual ~Launch();

  public:
    Launch(const Launch &);
    Launch	&operator=(const Launch &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone() const;

  public:
    static rtype::protocol::PartyID	Unique();

  public:
    rtype::protocol::PartyID	_id;
  };

  ////////////
  // Update //
  ////////////
  struct	Update : public ARequest
  {
  public:
    Update();
    Update(const std::string &partyName, rtype::protocol::Ruint8 availableSlots, rtype::protocol::Ruint8 maxPlayer,
	   rtype::protocol::Ruint8 partyPass, rtype::protocol::Status status);
    virtual ~Update();

  public:
    Update(const Update &);
    Update	&operator=(const Update &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone() const;

    std::string		_partyName;
    rtype::protocol::Ruint8		_availableSlots;
    rtype::protocol::Ruint8		_maxPlayers;
    rtype::protocol::Ruint8		_isPassword;
    rtype::protocol::Status	_status;
  };

  ///////////////////////////////
  // Canceled & finished party //
  ///////////////////////////////
  struct	Stopped : public ARequest
  {
  public:
    Stopped();
    virtual ~Stopped();

  public:
    Stopped(const Stopped &);
    Stopped	&operator=(const Stopped &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone() const;
  };
}

#endif /* PARTYREQUEST_H_ */
