#ifndef AGAMEREQUEST_H_
# define AGAMEREQUEST_H_

# include	"ProtocolTypes.hh"
# include	"ARequest.hh"

class AGameRequest : public ARequest
{
public:
  AGameRequest(const rtype::protocol::CodeID, rtype::protocol::SessionID,
	       rtype::protocol::game::Stamp stamp);
  AGameRequest(const rtype::protocol::CodeID);
  virtual ~AGameRequest();

public:
  AGameRequest(AGameRequest const&);
  AGameRequest& operator=(AGameRequest const&);

public:
  rtype::protocol::SessionID	SessionID() const;
  void				SessionID(const rtype::protocol::SessionID);
  rtype::protocol::game::Stamp			Stamp() const;
  void				Stamp(const rtype::protocol::game::Stamp);

public:
  virtual ARequest	*clone() const = 0;
  virtual Protocol	&serialize(Protocol &) const = 0;
  virtual Protocol	&unserialize(Protocol &) = 0;

protected:
  rtype::protocol::SessionID	_sessionID;
  rtype::protocol::game::Stamp				_stamp;
};

#endif /* AGAMEREQUEST_H_ */
