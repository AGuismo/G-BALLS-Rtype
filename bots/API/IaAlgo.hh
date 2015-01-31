#ifndef IAALGO_H_
# define IAALGO_H_

#if defined(WIN32)
#pragma		warning(disable: 4251)
# if defined(IAALGO_API_EXPORT)
# define	IAALGO_API	__declspec(dllexport)
# else
# define	IAALGO_API
# endif
# elif defined(linux)
#  define	IAALGO_API
#endif

#include	<list>
#include	<vector>
#include	"types.hh"
#include	"IAPlayer.hpp"

class IAALGO_API AIaAlgo
{
 public:
  AIaAlgo() : _type(0), _life(0), _isIa(true)
    {

    }
  virtual ~AIaAlgo() {};
  virtual int	algo(IAPlayer &players) = 0;
  virtual AIaAlgo		*clone() = 0;

  std::vector<game::Pos>	&pos() { return _pos; }
  std::list<game::Dir>		&fires() { return _fires; }
  game::Type			&type() { return _type; }
  game::Pos			&firePos() { return _firePos; }
  int				&life() { return _life; }
  bool				isIa() { return _isIa; }

 protected:
  std::vector<game::Pos>	_pos;
  std::list<game::Dir>		_fires;
  game::Pos			_firePos;
  game::Type			_type;
  int				_life;
  bool				_isIa;
};

#if defined(linux)
# undef		IAALGO_API
# define	IAALGO_API	extern
#endif

extern "C"
{
  IAALGO_API AIaAlgo	*getInstance();
}

#if defined(linux)
# undef		IAALGO_API
# define	IAALGO_API
#endif

#endif /* IAALGO_H_ */
