#ifndef ROOTREQUEST_H_
# define ROOTREQUEST_H_

# include	"RequestCode.hh"
# include	"ARequest.hh"

namespace	root
{
  class Shutdown : public ARequest
  {
  public:
    Shutdown();
    virtual ~Shutdown();

  public:
    Shutdown(Shutdown const&);
    Shutdown& operator=(Shutdown const&);

  public:
    Protocol			&serialize(Protocol &) const;
    Protocol			&unserialize(Protocol &);
    ARequest			*clone();
  };
}

#endif /* ROOTREQUEST_H_ */
