#ifndef LOADER_EXCEPTION_H
# define LOADER_EXCEPTION_H

# include	<string>
# include	<exception>

namespace	botLoader
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

#endif /* LOADER_EXCEPTION_H */
