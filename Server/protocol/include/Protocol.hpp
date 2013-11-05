#ifndef		PROTOCOL_H_
# define	PROTOCOL_H_

# include	<string>
# include	<deque>
# include	<vector>
// # include	"abs_sockets.h"
# include	"ARequest.hh"
# include	"types.hh"
# include	"RequestCode.hh"

# if defined(WIN32)
EXMP template class ABS_SOCKET_API std::vector<unsigned char>;
# endif
class Protocol
{
public:
  class ConstructRequest : public std::exception
  {
  public:
    virtual const char	*what() const throw();
    ConstructRequest(const std::string &) throw();
    ConstructRequest(const ConstructRequest &) throw();
    virtual ~ConstructRequest() throw();

  public:
    ConstructRequest& operator=(ConstructRequest const&) throw();

  private:
    std::string		_what;
  };

public:
  typedef Ruint8			Byte;
  typedef std::deque<Byte>		container_type;
  typedef container_type::size_type	size_type;

public:
  Protocol&                 operator<<(const Rint8);
  Protocol&                 operator<<(const Rint32);
  Protocol&                 operator<<(const Rint16);
  Protocol&                 operator<<(const Ruint8);
  Protocol&                 operator<<(const Ruint32);
  Protocol&                 operator<<(const Ruint16);
  Protocol&                 operator<<(const Rdouble);
  Protocol&                 operator<<(const Rfloat);
  Protocol&                 operator<<(const Rint8* s);
  Protocol&                 operator<<(const std::string & s);

  Protocol&                 operator>>(Rint8 &);
  Protocol&                 operator>>(Rint32 &);
  Protocol&                 operator>>(Rint16 &);
  Protocol&                 operator>>(Ruint8 &);
  Protocol&                 operator>>(Ruint32 &);
  Protocol&                 operator>>(Ruint16 &);
  Protocol&                 operator>>(Rdouble &);
  Protocol&                 operator>>(Rfloat &);
  Protocol&                 operator>>(Rint8* s);
  Protocol&                 operator>>(std::string & s);

public:
  Protocol();
  virtual ~Protocol();

public:
  template <typename T>
  T		push(const T, size_type count);

  template <typename T>
  T		&pop(T&);
  std::string	&pop(std::string &, size_type count);

public:
  Rbool		empty() const;
  Ruint32	size() const;
  Byte		*data();

public:
  static ARequest		*consume(std::vector<Byte> &, int &);
  static std::vector<Byte>	product(const ARequest &);

private:
  Protocol(Protocol const&);
  Protocol& operator=(Protocol const&);

private:
  std::deque<Byte>	_container;
  Byte			*_data;
};

template <typename T>
T		Protocol::push(const T val, size_type count)
{
  const Byte*	buffer = reinterpret_cast<const Byte*>(&val);

  for (size_t size = 0; size < sizeof(val) * count; size += sizeof(Byte))
    {
      _container.push_back(buffer[size]);
    }
  return (val);
}

template <typename T>
T		&Protocol::pop(T &val)
{
  Byte*		buffer = reinterpret_cast<Byte*>(&val);

  if (sizeof(T) > _container.size())
    throw ConstructRequest("Not enough size");
  for (size_t size = 0; size < sizeof(val); size += sizeof(Byte))
    {
      buffer[size] = _container.front();
      _container.pop_front();
    }
  return (val);
}

#endif /* PROTOCOL_H_ */
