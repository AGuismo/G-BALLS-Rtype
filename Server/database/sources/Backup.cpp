#include <string>
#include "Backup.hpp"
#define foreach(it, limit) for(typeof(limit) it = 0; it < limit; ++it)

using namespace save;

Backup::Backup() : _data(new Byte[0])
{
}

Backup::Backup(const Backup::Byte* data, Backup::size_type size) : _data(new Byte[0])
{
  _ctainer.resize(size);

  for (unsigned int i = 0; i < size; ++i)
    {
      _ctainer[i] = data[i];
    }
}

Backup::~Backup()
{
  delete[] _data;
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

save::Backup&		Backup::operator LC(bool, val);
save::Backup&		Backup::operator LC(char, val);
save::Backup&		Backup::operator LC(double, val);
save::Backup&		Backup::operator LC(float, val);
save::Backup&		Backup::operator LC(int, val);
save::Backup&		Backup::operator LC(long double, val);
save::Backup&		Backup::operator LC(long, val);
save::Backup&		Backup::operator LC(short, val);
save::Backup&		Backup::operator LC(unsigned char, val);
save::Backup&		Backup::operator LC(unsigned int, val);
save::Backup&		Backup::operator LC(unsigned long, val);
save::Backup&		Backup::operator LC(unsigned short, val);

save::Backup&		Backup::operator RC(bool, val);
save::Backup&		Backup::operator RC(char, val);
save::Backup&		Backup::operator RC(double, val);
save::Backup&		Backup::operator RC(float, val);
save::Backup&		Backup::operator RC(int, val);
save::Backup&		Backup::operator RC(long double, val);
save::Backup&		Backup::operator RC(long, val);
save::Backup&		Backup::operator RC(short, val);
save::Backup&		Backup::operator RC(unsigned char, val);
save::Backup&		Backup::operator RC(unsigned int, val);
save::Backup&		Backup::operator RC(unsigned long, val);
save::Backup&		Backup::operator RC(unsigned short, val);

save::Backup&		Backup::operator <<(const char * s)
{
  while ( push(*s++) );
  return (*this);
}

save::Backup&		Backup::operator >>(char * s)
{
  while ( pop(*s++) );
  return (*this);
}

save::Backup&		Backup::operator <<(const std::string & str)
{
  return (*this) << str.c_str();
}

save::Backup&		Backup::operator >>(std::string & str)
{
  char		c;

  str.clear();
  while ( pop(c) )
    {
      str.push_back(c);
    }
  return (*this);
}

Backup::Byte*		Backup::data(void)
{
  size_type	size = _ctainer.size();

  delete[] _data; _data = new Byte[size];

  for (unsigned int i = 0; i < size; ++i)
    {
      _data[i] = _ctainer[i];
    }
  return _data;
}

bool			Backup::empty(void) const
{
  return _ctainer.empty();
}

Backup::size_type	Backup::size(void) const
{
  return _ctainer.size();
}

invalid_argument::invalid_argument(const std::string msg) throw() :
  _what(msg)
{

}

invalid_argument::~invalid_argument() throw()
{

}

invalid_argument::invalid_argument(invalid_argument const&src) throw():
  _what(src._what)
{

}

invalid_argument& invalid_argument::operator=(invalid_argument const&src) throw()
{
  if (&src != this)
    {
      _what = src._what;
    }
  return (*this);
}

const char		*invalid_argument::what(void) const throw()
{
  return (_what.c_str());
}
