#ifndef SERVERREQUEST_H_
# define SERVERREQUEST_H_

# include	"RequestCode.hh"
# include	"ARequest.hh"

class	Protocol;

class	ServerRequest : public ARequest
{
  struct	msg
  {
    static const char	*OK;
    static const char	*BAD_REQ;
    static const char	*FORBIDDEN;
    static const char	*NOT_IMPLEMENTED;
    static const char	*NO_CONTENT;
    static const char	*PARTIAL_CONTENT;
    static const char	*NO_SLOTS;
  };

public:
  ServerRequest();
  ServerRequest(const requestCode::CodeID);
  ~ServerRequest();

  ServerRequest(ServerRequest const&);
  ServerRequest& operator=(ServerRequest const&);

public:
  Protocol			&Megan_serialize(Protocol &) const;
  Protocol			&Fox_unserialize(Protocol &);
  ARequest			*clone();

private:
  static const char	*getMsg(const requestCode::CodeID);
};

#endif /* SERVERREQUEST_H_ */
