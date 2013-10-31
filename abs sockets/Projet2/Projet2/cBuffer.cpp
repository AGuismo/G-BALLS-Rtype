// -----------------------------------------------------------------------------
// CBUFFER
// -----------------------------------------------------------------------------
// Last update Tue Jun 11 23:25:51 2013 lambert kevin

#include	"cBuffer.h"

using namespace net;

cBuffer::cBuffer()
{

}

cBuffer::~cBuffer()
{

}

cBuffer::size_type	cBuffer::look(std::vector<Byte> &buf,
				      cBuffer::size_type count)
{
  if (count > _buf.size())
    count = _buf.size();
  buf.insert(buf.begin(), _buf.end() - count, _buf.end());
  return (count);
}

cBuffer::size_type	cBuffer::read(std::vector<Byte> &buf,
				      cBuffer::size_type count)
{
  if (count > _buf.size())
    count = _buf.size();
  buf.insert(buf.begin(), _buf.end() - count, _buf.end());
  _buf.erase(_buf.end() - count, _buf.end());
  return (count);
}

cBuffer::size_type	cBuffer::write(const std::vector<Byte> &buf,
				       cBuffer::size_type count)
{
  if (count > buf.size())
    count = buf.size();
  _buf.insert(_buf.end(), buf.begin(), buf.begin() + count);
  return (count);
}

cBuffer::size_type	cBuffer::size() const
{
  return (_buf.size());
}

bool		cBuffer::empty() const
{
  return (_buf.empty());
}

#define LC(T, val)				\
  <<(const T val)				\
  {						\
    push(val);					\
    return (*this);				\
  }

#define RC(T, val)				\
  >>(T& val)					\
  {						\
    pop(val);					\
    return (*this);				\
  }

cBuffer&		cBuffer::operator LC(char, val);
cBuffer&		cBuffer::operator LC(double, val);
cBuffer&		cBuffer::operator LC(float, val);
cBuffer&		cBuffer::operator LC(int, val);
cBuffer&		cBuffer::operator LC(long double, val);
cBuffer&		cBuffer::operator LC(long, val);
cBuffer&		cBuffer::operator LC(short, val);
cBuffer&		cBuffer::operator LC(unsigned char, val);
cBuffer&		cBuffer::operator LC(unsigned int, val);
cBuffer&		cBuffer::operator LC(unsigned long, val);
cBuffer&		cBuffer::operator LC(unsigned short, val);

cBuffer&		cBuffer::operator RC(char, val);
cBuffer&		cBuffer::operator RC(double, val);
cBuffer&		cBuffer::operator RC(float, val);
cBuffer&		cBuffer::operator RC(int, val);
cBuffer&		cBuffer::operator RC(long double, val);
cBuffer&		cBuffer::operator RC(long, val);
cBuffer&		cBuffer::operator RC(short, val);
cBuffer&		cBuffer::operator RC(unsigned char, val);
cBuffer&		cBuffer::operator RC(unsigned int, val);
cBuffer&		cBuffer::operator RC(unsigned long, val);
cBuffer&		cBuffer::operator RC(unsigned short, val);

cBuffer&		cBuffer::operator <<(const char * s)
{
  while ( push(*s++) );
  return (*this);
}

cBuffer&		cBuffer::operator >>(char * s)
{
  while ( pop(*s++) );
  return (*this);
}

cBuffer&		cBuffer::operator <<(const std::string & str)
{
  return (*this) << str.c_str();
}

cBuffer&		cBuffer::operator >>(std::string & str)
{
  char		c;

  str.clear();
  while ( pop(c) )
    {
      str.push_back(c);
    }
  str.push_back(c);
  return (*this);
}
