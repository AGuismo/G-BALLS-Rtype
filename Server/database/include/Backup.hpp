#pragma once
#include <algorithm>
#include <cstring>
#include <string>
#include <deque>
#include <new>
#include "Salt.hpp"

namespace save
{
  class invalid_argument
  {
  public:
    invalid_argument(const std::string msg) throw();
    virtual ~invalid_argument() throw();

  public:
    invalid_argument(invalid_argument const&) throw();
    invalid_argument& operator=(invalid_argument const&) throw();

  public:
    const char		*what(void) const throw();

  protected:
    std::string		_what;
  };

  class Backup
  {
  public:
    typedef unsigned char Byte;

  private:
    typedef std::deque<Byte> container_type;
    container_type	_ctainer;
    Byte*		_data;

  public:
    typedef container_type::size_type size_type;

    Backup();
    Backup(const Byte* data, size_type size);
    ~Backup();

    Backup&			operator<<(const bool);
    Backup&			operator<<(const char);
    Backup&			operator<<(const double);
    Backup&			operator<<(const float);
    Backup&			operator<<(const int);
    Backup&			operator<<(const long double);
    Backup&			operator<<(const long);
    Backup&			operator<<(const short);
    Backup&			operator<<(const unsigned char);
    Backup&			operator<<(const unsigned int);
    Backup&			operator<<(const unsigned long);
    Backup&			operator<<(const unsigned short);
    Backup&			operator<<(const char* s);
    Backup&			operator<<(const std::string & s);

    Backup&			operator>>(bool&);
    Backup&			operator>>(char&);
    Backup&			operator>>(double&);
    Backup&			operator>>(float&);
    Backup&			operator>>(int&);
    Backup&			operator>>(long double&);
    Backup&			operator>>(long&);
    Backup&			operator>>(short&);
    Backup&			operator>>(unsigned char&);
    Backup&			operator>>(unsigned int&);
    Backup&			operator>>(unsigned long&);
    Backup&			operator>>(unsigned short&);
    Backup&			operator>>(char* s);
    Backup&			operator>>(std::string& s);

    friend std::ostream &	operator<<(std::ostream& stream, Backup& rhs)
    {
      Salt		salt;

      salt.update(rhs.data(), rhs.size());
      salt.final();
      stream << salt;
      stream.write((char*) rhs.data(), rhs.size());
      return stream;
    }

    friend std::istream &	operator>>(std::istream& file, Backup& rhs)
    {
      char			prev[Salt::LENGTH + 1];
      Salt			salt;

      file.seekg(0, file.end);
      const std::streamsize	size = file.tellg();
      file.seekg(0, file.beg);

      if (size < Salt::LENGTH) throw save::invalid_argument("wrong file size");

      file.read(prev, Salt::LENGTH);
      prev[Salt::LENGTH] = '\0';
      for (std::streamsize o = size - Salt::LENGTH; o > 0; o -= sizeof(Byte) )
	{
	  Byte	byte;

	  byte = file.get();
	  rhs.push(byte);
	}
      salt.update(rhs.data(), rhs.size());
      salt.final();

      if (salt != prev) throw save::invalid_argument("corrupted file");
      return file;
    }

    template <typename T>
    T			push(const T, size_type count = 1);

    template <typename T>
    T&			pop(T&);
    Byte*		data(void);
    bool		empty(void) const;
    size_type		size(void) const;
    std::string		push(const std::string &, size_type count);
    std::string		&pop(std::string &, size_type count);
  };

  template <typename T>
  T			Backup::push(const T val, size_type count)
  {
    const Byte*		buffer = reinterpret_cast<const Byte*>(&val);

    for (size_t size = 0; size < sizeof(val) * count; size += sizeof(Byte))
      {
	_ctainer.push_back(buffer[size]);
      }
    return val;
  }

  template <typename T>
  T&			Backup::pop(T& val)
  {
    Byte*		buffer = reinterpret_cast<Byte*>(&val);

    for (size_t size = 0; size < sizeof(val); size += sizeof(Byte) )
      {
	buffer[size] = _ctainer.front();
	_ctainer.pop_front();
      }
    return val;
  }
}
