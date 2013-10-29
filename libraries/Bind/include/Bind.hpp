#ifndef BIND_H_
# define BIND_H_

class Bind
{
  template <typename Ret>
  static Bind0p	&Bind(Bind0p::Func f)
  {
    return (Bind0p<Bind0p::Func>(f))
  }
  static Bind1p	&Bind(Bind1p::Func f)
  {
    return (Bind1p<Bind1p::Func>(f))
  }
  friend class Bind0p;
  friend class Bind1p;
};

#include	"Bind0p.hpp"
#include	"Bind1p.hpp"

#endif /* BIND_H_ */
