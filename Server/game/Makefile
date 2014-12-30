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

DIR.DEPS=	../../libraries/
DIR.THREADS=	./$(DIR.DEPS)/Thread/Threads/
DIR.NET=	./$(DIR.DEPS)/network/network/
DIR.BIND=	./$(DIR.DEPS)/Bind
DIR.PROT=	./$(DIR.DEPS)/protocol/
DIR.LOG=	./$(DIR.DEPS)/log
DIR.MENU=	../menu/
DIR.LOADER=	../loader/
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
