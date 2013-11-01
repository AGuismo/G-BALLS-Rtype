#ifndef TYPES_H_
# define TYPES_H_

#if defined(WIN32)

# include			<windows.h>

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

#endif /* TYPES_H_ */
