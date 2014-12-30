#ifndef NETEXCEPTION_H_
# define NETEXCEPTION_H_

#include	<stdexcept>
#include	<string>
#include	"abs_sockets.h"

#if defined(WIN32)
#pragma warning( disable : 4251)
#endif

namespace net
{
	class ABS_SOCKET_API Exception : public std::exception
  {
  public:
    Exception(const std::string &) throw();
    Exception(Exception const&) throw();
    virtual ~Exception() throw();

  public:
    Exception& operator=(Exception const&) throw();

  public:
    virtual const char	*what() const throw();

  protected:
    std::string		_what;
  };

}

#endif /* NETEXCEPTION_H_ */
