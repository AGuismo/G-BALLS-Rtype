#ifndef SESSIONREQUEST_H_
# define SESSIONREQUEST_H_

# include	"ARequest.hh"

class SessionRequest : public ARequest
{
public:
  SessionRequest();
  SessionRequest(rtype::protocol::SessionID);
  virtual ~SessionRequest();

public:
  SessionRequest(SessionRequest const&);
  SessionRequest& operator=(SessionRequest const&);

public:
  virtual Protocol	&serialize(Protocol &) const;
  virtual Protocol	&unserialize(Protocol &);
  ARequest		*clone() const;

public:
  static rtype::protocol::SessionID	Unique(void);

public:
  rtype::protocol::SessionID	SessionID() const;
  void				SessionID(rtype::protocol::SessionID);

private:
  rtype::protocol::SessionID	_sessionID;
};

#endif /* SESSIONREQUEST_H_ */
