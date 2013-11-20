#include	<iostream>
#include	"RequestFactory.hh"
#include	"Protocol.hpp"

Protocol::Protocol():
  _data(0)
{

}

Protocol::~Protocol()
{
  delete [] _data;
}

Rbool	Protocol::empty() const
{
  return (_container.empty());
}

Ruint32	Protocol::size() const
{
  return (_container.size());
}

Protocol::Byte		*Protocol::data()
{
  const size_type	size = _container.size();

  delete [] _data;
  _data = new Byte[size];
  for (size_type it = 0; it < size; ++it)
    {
      _data[it] = _container[it];
    }
  return (_data);
}

#define LC(T, val)				\
  <<(const T val)				\
  {						\
    push(val, 1);				\
    return (*this);				\
  }

#define RC(T, val)				\
  >>(T& val)					\
  {						\
    pop(val);					\
    return (*this);				\
  }

Protocol&	Protocol::operator LC(Rint8, val);
Protocol&	Protocol::operator LC(Rint16, val);
Protocol&	Protocol::operator LC(Rint32, val);
Protocol&	Protocol::operator LC(Ruint8, val);
Protocol&	Protocol::operator LC(Ruint16, val);
Protocol&	Protocol::operator LC(Ruint32, val);
Protocol&	Protocol::operator LC(Rdouble, val);
Protocol&	Protocol::operator LC(Rfloat, val);

Protocol&	Protocol::operator RC(Rint8, val);
Protocol&	Protocol::operator RC(Rint16, val);
Protocol&	Protocol::operator RC(Rint32, val);
Protocol&	Protocol::operator RC(Ruint8, val);
Protocol&	Protocol::operator RC(Ruint16, val);
Protocol&	Protocol::operator RC(Ruint32, val);
Protocol&	Protocol::operator RC(Rdouble, val);
Protocol&	Protocol::operator RC(Rfloat, val);

Protocol&	Protocol::operator<<(const Rint8* s)
{
  while (*s && push(*s++, 1));
  return (*this);
}

Protocol&	Protocol::operator>>(Rint8* s)
{
  while (*s && pop(*s++));
  return (*this);
}

Protocol&	Protocol::operator<<(const std::string & s)
{
  const char	*arr = s.c_str();

  for (std::string::size_type it = 0; it < s.size(); ++it)
    push(arr[it], 1);
  return (*this);
}

Protocol&	Protocol::operator>>(std::string & s)
{
  pop(s, s.size());
  return (*this);
}

std::string		&Protocol::pop(std::string &val, Protocol::size_type count)
{
  val.clear();
  val.insert(val.begin(), _container.begin(), _container.begin() + count);
  _container.erase(_container.begin(), _container.begin() + count);
  return (val);
}

std::string		Protocol::push(const std::string &val, Protocol::size_type count)
{
  const Byte*	buffer = reinterpret_cast<const Byte*>(val.c_str());

  for (size_t size = 0; size < sizeof(*val.c_str()) * count; size += sizeof(Byte))
    {
      _container.push_back(buffer[size]);
    }
  return (val);
}

ARequest		*Protocol::consume(std::vector<Byte> &input, int &extracted)
{
  Protocol		p;
  requestCode::CodeID	code;
  ARequest		*req;

#if defined(DEBUG)
  std::cerr << "Protocol::consume(): " << input.size() << std::endl;
#endif
  p._container.clear();
  p._container.insert(p._container.begin(), input.begin(), input.end());
  p >> code;
#if defined(DEBUG)
  std::cout << "Protocol::consume(): " << "Request id -" << code << "- Contruction..." << std::endl;
#endif
  try
    {
      req = request::Factory::factory(p, code);
    }
  catch (ARequest::Exception &e)
    {
      throw ConstructRequest(e.what());
    }
  extracted = input.size() - p._container.size();
  req->code(code);
#if defined(DEBUG)
  std::cout << "Protocol::consume(): " << "Request id -" << code << "- Complete" << std::endl;
#endif
  return (req);
}

std::vector<Protocol::Byte>	Protocol::product(const ARequest &output)
{
  Protocol		p;
  std::vector<Byte>	bytes;

  p._container.clear();
  request::Factory::factory(p, output);
  bytes.insert(bytes.begin(), p._container.begin(), p._container.end());
  return (bytes);
}

Protocol::ConstructRequest::ConstructRequest(const std::string &what) throw() :
  _what(what)
{

}

Protocol::ConstructRequest::~ConstructRequest() throw()
{

}

Protocol::ConstructRequest::ConstructRequest(ConstructRequest const &src) throw() :
  _what(src._what)
{

}

Protocol::ConstructRequest	&Protocol::ConstructRequest::operator=(ConstructRequest const & src) throw()
{
  if (this != &src)
    {
      _what = src._what;
    }
  return (*this);
}

const char		*Protocol::ConstructRequest::what() const throw()
{
  return (_what.c_str());
}
