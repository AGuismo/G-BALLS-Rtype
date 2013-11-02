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
