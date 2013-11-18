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
    ~Start();

  public:
    Start(const Start &);
    Start	&operator=(const Start &);

  public:
    Protocol			&serialize(Protocol &) const;
    Protocol			&unserialize(Protocol &);
    ARequest			*clone();
  };

  struct	List : public ARequest
  {
  public:
    List();
    ~List();

  public:
    List(const List &);
    List	&operator=(const List &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone();
  };

  struct	Create : public ARequest
  {
    static const Ruint8	PASS = 0;
    static const Ruint8	NO_PASS = 1;

  public:
    Create();
    Create(const std::string &partyName, Ruint8 nbPlayers);
    Create(const std::string &partyName, Ruint8 nbPlayers, requestCode::PasswordType pass);
    ~Create();

  public:
    Create(const Create &);
    Create	&operator=(const Create &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone();

  public:
    std::string			_partyName;
    Ruint8			_maxPlayers;
    Ruint8			_isPassword;
    requestCode::PasswordType	_partyPass;
  };

  struct	Cancel : public ARequest
  {
  public:
    Cancel();
    ~Cancel();

  public:
    Cancel(const Cancel &);
    Cancel	&operator=(const Cancel &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone();
  };

  struct	Join : public ARequest
  {
  public:
    Join(const std::string &partyName);
    Join(const std::string &partyName, requestCode::PasswordType pass);
    Join();
    ~Join();

  public:
    Join(const Join &);
    Join	&operator=(const Join &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone();

  public:
    std::string			_partyName;
    Ruint8			_maxPlayers;
    Ruint8			_isPassword;
    requestCode::PasswordType	_partyPass;
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
    Launch(requestCode::PartyID);
    ~Launch();

  public:
    Launch(const Launch &);
    Launch	&operator=(const Launch &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone();

  public:
    static requestCode::PartyID	Unique();

  public:
    requestCode::PartyID	_id;
  };

  ////////////
  // Update //
  ////////////
  struct	Update : public ARequest
  {
  public:
    Update();
    Update(const std::string &partyName, Ruint8 availableSlots, Ruint8 maxPlayer,
	   Ruint8 partyPass, Ruint8 status);
    ~Update();

  public:
    Update(const Update &);
    Update	&operator=(const Update &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone();

    std::string	_partyName;
    Ruint8	_availableSlots;
    Ruint8	_maxPlayers;
    Ruint8	_isPassword;
    Ruint8	_status;
  };

  ///////////////////////////////
  // Canceled & finished party //
  ///////////////////////////////
  struct	Stopped : public ARequest
  {
  public:
    Stopped();
    ~Stopped();

  public:
    Stopped(const Stopped &);
    Stopped	&operator=(const Stopped &);

  public:
    Protocol	&serialize(Protocol &) const;
    Protocol	&unserialize(Protocol &);
    ARequest	*clone();
  };
}

#endif /* PARTYREQUEST_H_ */
