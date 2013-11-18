## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libmenu.a


SRCS =	      	MenuManager.cpp		\
		MenuException.cpp	\
		MenuClient.cpp		\
		MenuGame.cpp		\

DIR.THREADS=	../deps/Threads/
DIR.NETWORK=	../deps/network/
DIR.DB=		../database/
DIR.PROT=	../protocol/
DIR.BIND=	../deps/Bind/
DIR.GAME=	../game/

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I$(DIR.H) -I$(DIR.THREADS)/include -I$(DIR.NETWORK)/include -I../include
F.I	     += -I$(DIR.PROT)/include -I$(DIR.BIND)/include -I$(DIR.GAME)/include
F.I	     += -I$(DIR.DB)/include
F.D	     +=


all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
