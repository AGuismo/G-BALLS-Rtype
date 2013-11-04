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
  while (push(*s++, 1));
  return (*this);
}

Protocol&	Protocol::operator>>(Rint8* s)
{
  while (pop(*s++));
  return (*this);
}

Protocol&	Protocol::operator<<(const std::string & s)
{
  return (*this << s.c_str());
}

Protocol&	Protocol::operator>>(std::string & s)
{
  Rint8		c;

  s.clear();
  while (pop(c))
    {
      s.push_back(c);
    }
  return (*this);
}

ARequest		*Protocol::consume(std::vector<net::cBuffer::Byte> &input)
{
  Protocol		p;
  requestCode::CodeID	code;

  std::cerr << input.size() << std::endl;
  p._container.clear();
  p._container.insert(p._container.begin(), input.begin(), input.end());
  p >> code;
  try
    {
      return (request::Factory::factory(p, code));
    }
  catch (ARequest::Exception &e)
    {
      throw ConstructRequest(e.what());
    }
}

std::vector<net::cBuffer::Byte>		Protocol::product(const ARequest &output)
{
  Protocol				p;
  std::vector<net::cBuffer::Byte>	bytes;

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
