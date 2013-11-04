#ifndef AREQUEST_H_
# define AREQUEST_H_

# include	<string>
# include	<exception>
# include	"types.hh"
# include	"RequestCode.hh"
# include	"ITransformers.hh"

class ARequest : public ITransformers
{
public:
  class Exception : public std::exception
  {
  public:
    virtual const char	*what() const throw();
    Exception(const std::string &) throw();
    Exception(const Exception &) throw();
    virtual ~Exception() throw();

  public:
    Exception& operator=(Exception const&) throw();

  private:
    std::string		_what;
  };

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
