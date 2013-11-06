## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libgame.a


SRCS =	      	GameManager.cpp		\
		GameException.cpp	\
		GameClient.cpp		\
		Boss.cpp		\
		ElapsedTime.cpp		\
		Entity.cpp		\
		Missile.cpp		\
		Game.cpp		\
		Clock.cpp		\
		Player.cpp		\
		Referee.cpp		\
		Time.cpp		\

DIR.THREADS=	../deps/Threads
DIR.BIND=	../deps/Bind
DIR.MENU=	../menu/

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I $(DIR.H) -I$(DIR.THREADS)/include -I$(DIR.BIND)/include -I../include -I$(DIR.MENU)/include
F.D	     +=

all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
