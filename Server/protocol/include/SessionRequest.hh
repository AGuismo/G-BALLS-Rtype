#ifndef SESSIONREQUEST_H_
# define SESSIONREQUEST_H_

# include	"ARequest.hh"

class SessionRequest : public ARequest
{
public:
  SessionRequest();
  SessionRequest(requestCode::SessionID);
  virtual ~SessionRequest();

public:
  SessionRequest(SessionRequest const&);
  SessionRequest& operator=(SessionRequest const&);

public:
  virtual Protocol	&serialize(Protocol &) const;
  virtual Protocol	&unserialize(Protocol &);
  ARequest		*clone();

public:
  static requestCode::SessionID	Unique(void);

public:
  requestCode::SessionID	SessionID() const;
  void				SessionID(requestCode::SessionID);

private:
  requestCode::SessionID	_sessionID;
};

#endif /* SESSIONREQUEST_H_ */
