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

std::string		&Backup::pop(std::string &val, Backup::size_type count)
{
  val.clear();
  val.insert(val.begin(), _ctainer.begin(), _ctainer.begin() + count);
  _ctainer.erase(_ctainer.begin(), _ctainer.begin() + count);
  return (val);
}

std::string		Backup::push(const std::string &val, Backup::size_type count)
{
  const Byte*	buffer = reinterpret_cast<const Byte*>(val.c_str());

  for (size_t size = 0; size < sizeof(*val.c_str()) * count; size += sizeof(Byte))
    {
      _ctainer.push_back(buffer[size]);
    }
  return (val);
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
