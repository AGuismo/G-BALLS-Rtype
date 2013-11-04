#ifndef AREQUEST_H_
# define AREQUEST_H_

# include	"types.hh"
# include	"RequestCode.hh"
# include	"ITransformers.hh"

class ARequest : public ITransformers
{
public:

public:
  ARequest(const requestCode::CodeID);
  virtual ~ARequest();

public:
  requestCode::CodeID	code() const;
  void			code(const requestCode::CodeID);

public:
  ARequest(ARequest const&);
  ARequest& operator=(ARequest const&);

public:
  virtual Protocol	&Megan_serialize(Protocol &);
  virtual Protocol	&Fox_unserialize(Protocol &);

protected:
  requestCode::CodeID	_code;
};

#endif /* AREQUEST_H_ */
