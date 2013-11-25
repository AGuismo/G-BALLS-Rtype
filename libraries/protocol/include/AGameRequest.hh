#ifndef AGAMEREQUEST_H_
# define AGAMEREQUEST_H_

# include	"ARequest.hh"

class AGameRequest : public ARequest
{
public:
  AGameRequest(const requestCode::CodeID, requestCode::SessionID);
  virtual ~AGameRequest();

public:
  AGameRequest(AGameRequest const&);
  AGameRequest& operator=(AGameRequest const&);

public:
  requestCode::SessionID	SessionID() const;
  void				SessionID(const requestCode::SessionID);

public:
  virtual ARequest	*clone() = 0;
  virtual Protocol	&serialize(Protocol &) const = 0;
  virtual Protocol	&unserialize(Protocol &) = 0;

protected:
  requestCode::SessionID	_sessionID;
};

#endif /* AGAMEREQUEST_H_ */
