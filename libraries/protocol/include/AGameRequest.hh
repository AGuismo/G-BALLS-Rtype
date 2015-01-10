#ifndef AGAMEREQUEST_H_
# define AGAMEREQUEST_H_

# include	"ARequest.hh"

class AGameRequest : public ARequest
{
public:
	AGameRequest(const requestCode::CodeID, requestCode::SessionID, game::Stamp);
	AGameRequest(const requestCode::CodeID);
	virtual ~AGameRequest();

public:
	AGameRequest(AGameRequest const&);
	AGameRequest& operator=(AGameRequest const&);

public:
	requestCode::SessionID	SessionID() const;
	void				SessionID(const requestCode::SessionID);
	game::Stamp			Stamp() const;
	void				Stamp(const game::Stamp);

public:
	virtual ARequest	*clone() const = 0;
	virtual Protocol	&serialize(Protocol &) const = 0;
	virtual Protocol	&unserialize(Protocol &) = 0;

protected:
	requestCode::SessionID	_sessionID;
	game::Stamp				_stamp;
};

#endif /* AGAMEREQUEST_H_ */
