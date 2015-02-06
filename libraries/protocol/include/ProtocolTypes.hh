#ifndef TYPES_H_
# define TYPES_H_

# if defined(WIN32)
#  include			<windows.h>
# elif defined(linux)
#  include			<stdint.h>
# else
#  error "Unsupported Operating System"
# endif // !OS

# include	<string>

namespace	rtype
{

  namespace	protocol
  {

#if defined(WIN32)

    typedef __int8		Rbool;
    typedef __int8		Rint8;
    typedef __int16		Rint16;
    typedef __int32		Rint32;

    typedef unsigned __int8	Ruint8;
    typedef unsigned __int16	Ruint16;
    typedef unsigned __int32	Ruint32;

    typedef float		Rfloat;
    typedef double		Rdouble;

#elif defined(linux)

    typedef int8_t		Rbool;
    typedef int8_t		Rint8;
    typedef int16_t		Rint16;
    typedef int32_t		Rint32;

    typedef uint8_t		Ruint8;
    typedef uint16_t		Ruint16;
    typedef uint32_t		Ruint32;

    typedef float		Rfloat;
    typedef double		Rdouble;

#endif

    namespace		database
    {
      typedef Ruint8	Rights;
    };

    namespace	game
    {
      typedef Ruint16	ID;
      typedef Ruint16	Dir;
      typedef Ruint8	Event;
      typedef Ruint16	FullType;
      typedef Ruint8	MinorType;
      typedef Ruint8	MajorType;
      typedef Ruint16	Pos;
      typedef Rint8	TypeBuff;
      typedef Ruint32	Stamp;
      typedef Ruint8	Shoot;
    };

    typedef Ruint16	CodeID;
    typedef std::string	PasswordType;
    typedef Ruint16	UsernameLen;
    typedef Ruint16	PartynameLen;
    typedef Ruint16	SessionID;
    typedef Ruint16	PartyID;
    typedef Ruint8	Status;

    struct rtypeAuth
    {
      static const int	PASS_SIZE = 32;
    };

  };
};
#endif /* TYPES_H_ */
