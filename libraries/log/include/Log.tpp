#include	<ctime>

namespace	log
{

  template <typename T>
  Log		&Log::operator<<(const T &val)
  {
    _buffer << val;
    return (*this);
  }

}
