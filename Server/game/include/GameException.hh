#ifndef GAMEEXCEPTION_H_
# define GAMEEXCEPTION_H_

# include	<string>
# include	<exception>

namespace	game
{
  class		Exception : public std::exception
  {
  public:
    Exception(const std::string &) throw();
    Exception(Exception const&) throw();
    virtual ~Exception() throw();

  public:
    const char	*what() const throw();

  public:
    Exception& operator=(Exception const&) throw();

  protected:
    std::string	_what;
  };
}

#endif /* GAMEEXCEPTION_H_ */
