#ifndef BIND_H_
# define BIND_H_

#include	"Bind4p.hpp"
#include	"Bind3p.hpp"
#include	"Bind2p.hpp"
#include	"Bind1p.hpp"
#include	"Bind0p.hpp"

struct Func
{
  template <typename Ret>
  static Function<Ret, void>	Bind(Ret (*f)());
  template <typename Ret, typename P1>
  static Function<Ret, P1>	Bind(Ret (*f)(P1), P1 _1);
  template <typename Ret, typename P1, typename P2>
  static Function<Ret, P1, P2>	Bind(Ret (*f)(P1, P2), P1 _1, P2 _2);
  template <typename Ret, typename P1, typename P2, typename P3>
  static Function<Ret, P1, P2, P3>	Bind(Ret (*f)(P1, P2, P3), P1 _1, P2 _2, P3 _3);
  template <typename Ret, typename P1, typename P2, typename P3, typename P4>
  static Function<Ret, P1, P2, P3, P4>	Bind(Ret (*f)(P1, P2, P3, P4), P1 _1, P2 _2, P3 _3, P4 _4);
};

template <typename Ret>
Function<Ret>	Func::Bind(Ret (*f)())
{
  return (Function<Ret, void>(f));
}

template <typename Ret, typename P1>
Function<Ret, P1>	Func::Bind(Ret (*f)(P1), P1 _1)
{
  return (Function<Ret, P1>(f, _1));
}

template <typename Ret, typename P1, typename P2>
Function<Ret, P1, P2>	Func::Bind(Ret (*f)(P1, P2), P1 _1, P2 _2)
{
  return (Function<Ret, P1, P2>(f, _1, _2));
}

template <typename Ret, typename P1, typename P2, typename P3>
Function<Ret, P1, P2, P3>	Func::Bind(Ret (*f)(P1, P2, P3), P1 _1, P2 _2, P3 _3)
{
  return (Function<Ret, P1, P2, P3>(f, _1, _2, _3));
}

template <typename Ret, typename P1, typename P2, typename P3, typename P4>
Function<Ret, P1, P2, P3, P4>	Func::Bind(Ret (*f)(P1, P2, P3, P4), P1 _1, P2 _2, P3 _3, P4 _4)
{
  return (Function<Ret, P1, P2, P3, P4>(f, _1, _2, _3, _4));
}

#endif /* BIND_H_ */
