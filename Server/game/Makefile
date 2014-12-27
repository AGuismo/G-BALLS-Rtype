## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libgame.a


SRCS =	      	GameManager.cpp		\
		GameException.cpp	\
		GameClient.cpp		\
		GamePool.cpp		\
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
DIR.LOG=	../deps/log/
DIR.BIND=	../deps/Bind
DIR.LOADER=	../loader/
DIR.PROT=	../deps/protocol/
DIR.IAAPI=	../../bots/API/

F.C	     +=	-W -Wall 
F.I	     +=	-I $(DIR.H) -I$(DIR.THREADS)/include -I$(DIR.BIND)/include -I../include
F.I	     += -I$(DIR.IAAPI) -I$(DIR.NET)/include -I$(DIR.LOG)/include
F.I	     += -I$(DIR.LOADER)/include -I$(DIR.PROT)/include
F.D	     +=

all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
