## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libmenu.a


SRCS =	      	MenuManager.cpp		\
		MenuException.cpp	\
		MenuClient.cpp		\
		MenuGame.cpp		\

DIR.DEPS=	../../libraries/
DIR.THREADS=	./$(DIR.DEPS)/Thread/Threads/
DIR.NETWORK=	./$(DIR.DEPS)/network/network/
DIR.PROT=	./$(DIR.DEPS)/protocol/
DIR.BIND=	./$(DIR.DEPS)/Bind/
DIR.DB=		../database/
DIR.LOAD=	../loader/
DIR.GAME=	../game/
DIR.IAAPI=	../../bots/API/

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I$(DIR.THREADS)/include -I$(DIR.NETWORK)/include -I../include
F.I	     += -I$(DIR.PROT)/include -I$(DIR.BIND)/include -I$(DIR.GAME)/include
F.I	     += -I$(DIR.DB)/include -I$(DIR.LOAD)/include -I$(DIR.IAAPI)/include
F.D	     +=


all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
