#pragma once
#include "MD5.hh"

class Salt
{
public:
  typedef MD5::size_type size_type;
  static const size_type	LENGTH = 32;
  static size_type		SALT;

  void			update(const void * buf, size_type length);
  Salt&			final(void);
  std::string			digest(void) const;
  bool			operator==(const std::string& rhs) const;
  bool			operator!=(const std::string& rhs) const;

  friend std::ostream &	operator<<(std::ostream& out, const Salt& rhs)
  {
    return out << rhs.digest();
  }

private:
  MD5			md5;
};
