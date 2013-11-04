## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libprotocol.a


SRCS =	      	ARequest.cpp		\
		AuthRequest.cpp		\
		Protocol.cpp		\
		RequestFactory.cpp	\

DIR.BIND=	../deps/Bind
DIR.NET=	../deps/network

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I $(DIR.H) -I$(DIR.BIND)/include -I$(DIR.NET)/include -I../include
F.D	     +=


all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
