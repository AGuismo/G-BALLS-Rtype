#ifndef PARTYREQUEST_H_
# define PARTYREQUEST_H_

# include	"RequestCode.hh"
# include	"ARequest.hh"

namespace	Party
{
  struct	Start : public ARequest
  {
  public:
    Start();
    ~Start();

  public:
    Start(const Start &);
    Start	&operator=(const Start &);

  public:
    Protocol			&Megan_serialize(Protocol &) const;
    Protocol			&Fox_unserialize(Protocol &);
    ARequest			*clone();
  };
}

#endif /* PARTYREQUEST_H_ */
