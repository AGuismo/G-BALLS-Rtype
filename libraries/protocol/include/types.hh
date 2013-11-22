#ifndef TYPES_H_
# define TYPES_H_

# include	<string>

#if defined(WIN32)

# include			<windows.h>

typedef __int8			Rbool;
typedef __int8			Rint8;
typedef __int16			Rint16;
typedef __int32			Rint32;

typedef unsigned __int8		Ruint8;
typedef unsigned __int16	Ruint16;
typedef unsigned __int32	Ruint32;

typedef float			Rfloat;
typedef double			Rdouble;

#elif defined(linux)

# include			<stdint.h>

typedef int8_t			Rbool;
typedef int8_t			Rint8;
typedef int16_t			Rint16;
typedef int32_t			Rint32;

typedef uint8_t			Ruint8;
typedef uint16_t		Ruint16;
typedef uint32_t		Ruint32;

typedef float			Rfloat;
typedef double			Rdouble;

#else
# error "Unsupported Operating System"
#endif

namespace	database
{
  typedef Ruint8	Rights;
};

namespace	game
{
  typedef Ruint16	ID;
  typedef Ruint8	Dir;
  typedef Ruint8	Type;
  typedef Ruint16	Pos;
  typedef Rint8		TypeBuff;
}

namespace	requestCode
{
  typedef Ruint16	CodeID;
  typedef std::string	PasswordType;
  typedef Ruint16	UsernameLen;
  typedef Ruint16	PartynameLen;
  typedef Ruint16	SessionID;
  typedef Ruint16	PartyID;
}

struct rtype
{
	static const int	PASS_SIZE = 32;
};

#endif /* TYPES_H_ */
