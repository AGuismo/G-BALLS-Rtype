#pragma once

#include	<cstddef>
#include	<vector>
#include	<deque>
#include	<string>
#include	"abs_sockets.h"
//#include	"assert.h"

EXMP template class ABS_SOCKET_API std::vector<unsigned char>;
namespace	net
{
  class ABS_SOCKET_API cBuffer
  {
  public:
    typedef unsigned char				Byte;
    typedef std::vector<cBuffer::Byte>			stor_type;
    typedef std::vector<cBuffer::Byte>::size_type	size_type;

  public:
    cBuffer();
    virtual ~cBuffer();

  public:
    cBuffer::size_type	look(std::vector<Byte> &buf, cBuffer::size_type count);
    cBuffer::size_type	read(std::vector<Byte> &buf, cBuffer::size_type count);
    cBuffer::size_type	write(const std::vector<Byte> &buf, cBuffer::size_type count);
    cBuffer::size_type	size(void) const;
    bool			empty(void) const;

    cBuffer&		operator<<(const char);
    cBuffer&		operator<<(const double);
    cBuffer&		operator<<(const float);
    cBuffer&		operator<<(const int);
    cBuffer&		operator<<(const long double);
    cBuffer&		operator<<(const long);
    cBuffer&		operator<<(const short);
    cBuffer&		operator<<(const unsigned char);
    cBuffer&		operator<<(const unsigned int);
    cBuffer&		operator<<(const unsigned long);
    cBuffer&		operator<<(const unsigned short);
    cBuffer&		operator<<(const char* s);
    cBuffer&		operator<<(const std::string & s);

    cBuffer&		operator>>(char&);
    cBuffer&		operator>>(double&);
    cBuffer&		operator>>(float&);
    cBuffer&		operator>>(int&);
    cBuffer&		operator>>(long double&);
    cBuffer&		operator>>(long&);
    cBuffer&		operator>>(short&);
    cBuffer&		operator>>(unsigned char&);
    cBuffer&		operator>>(unsigned int&);
    cBuffer&		operator>>(unsigned long&);
    cBuffer&		operator>>(unsigned short&);
    cBuffer&		operator>>(char* s);
    cBuffer&		operator>>(std::string& s);

    template <typename T>
      T			push(const T, size_type count = 1);

    template <typename T>
      T&			pop(T&);

  private:
    cBuffer(cBuffer const&);
    cBuffer& operator=(cBuffer const&);

  private:
    std::vector<cBuffer::Byte>	_buf;
  };

  template <typename T>
    T			cBuffer::push(const T val, size_type count)
    {
      const Byte*		buffer = reinterpret_cast<const Byte*>(&val);

      for (size_t size = 0; size < sizeof(val) * count; size += sizeof(Byte))
	{
	  _buf.push_back(buffer[size]);
	}
      return val;
    }

  template <typename T>
    T&			cBuffer::pop(T& val)
    {
      Byte*		buffer = reinterpret_cast<Byte*>(&val);


      for (size_t size = 0; size < sizeof(val); size += sizeof(Byte) )
	{
	  buffer[size] = _buf.front();
	  _buf.erase(_buf.begin());
	}
      return val;
    }
}

//#include "cBuffer.tcc"
