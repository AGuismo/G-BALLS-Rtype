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



  // Server Responses

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
    requestCode::PartyID	PartyID() const;
    void			PartyID(requestCode::PartyID);

  public:
    static requestCode::PartyID	Unique();

  private:
    requestCode::PartyID	_id;
  };

}

#endif /* PARTYREQUEST_H_ */
