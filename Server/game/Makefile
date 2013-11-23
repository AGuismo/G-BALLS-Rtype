## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libgame.a


SRCS =	      	GameManager.cpp		\
		GameException.cpp	\
		GameClient.cpp		\
		Boss.cpp		\
		BaseIA.cpp		\
		IA.cpp			\
		BaseBoss.cpp		\
		Bonus.cpp		\
		ElapsedTime.cpp		\
		Entity.cpp		\
		Missile.cpp		\
		Game.cpp		\
		Clock.cpp		\
		Player.cpp		\
		Referee.cpp		\
		Time.cpp		\

DIR.THREADS=	../deps/Threads
DIR.NET=	../deps/network
DIR.BIND=	../deps/Bind
DIR.MENU=	../menu/
DIR.PROT=	../deps/protocol/

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I $(DIR.H) -I$(DIR.THREADS)/include -I$(DIR.BIND)/include -I../include
F.I	     += -I$(DIR.NET)/include -I$(DIR.MENU)/include -I$(DIR.PROT)/include
F.D	     +=

all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
