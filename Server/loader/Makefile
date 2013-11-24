## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libloader.a


SRCS =	      	LoaderManager.cpp	\
		LoaderException.cpp	\
		CheckFileAbstract.cpp	\
		DynamicAbstract.cpp	\

DIR.THREADS=	../deps/Threads
DIR.BIND=	../deps/Bind
DIR.PROTO=	../deps/protocol
DIR.IAAPI=	../../bots/API/

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I $(DIR.H) -I$(DIR.BIND)/include -I$(DIR.PROTO)/include -I$(DIR.THREADS)/include
F.I	     += -I../include -I$(DIR.IAAPI)/include
F.D	     +=


all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
