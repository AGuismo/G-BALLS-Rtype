#ifndef SERVERREQUEST_H_
# define SERVERREQUEST_H_

# include	"RequestCode.hh"
# include	"ARequest.hh"

class	Protocol;

class	ServerRequest : public ARequest
{

public:
  ServerRequest();
  ServerRequest(const requestCode::CodeID);
  ~ServerRequest();

  ServerRequest(ServerRequest const&);
  ServerRequest& operator=(ServerRequest const&);

public:
  Protocol			&serialize(Protocol &) const;
  Protocol			&unserialize(Protocol &);
  ARequest			*clone();
};

#endif /* SERVERREQUEST_H_ */
