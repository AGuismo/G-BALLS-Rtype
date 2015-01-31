## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libgame.a

SRCS =	      	Animation.cpp		\
		AudioManager.cpp	\
		Game.cpp		\
		GameWindow.cpp		\
		Layer.cpp		\
		LayerManager.cpp	\
		TextureManager.cpp	\
		EventManager.cpp	\
		Timer.cpp		\

DIR.SFML=	/usr/local/
DIR.LIB=	../../libraries/
DIR.THREAD=	./$(DIR.LIB)/Thread/Threads
DIR.BIND=	./$(DIR.LIB)/Bind
DIR.PROT=	./$(DIR.LIB)/protocol
DIR.REF=	./$(DIR.LIB)/Referee/
DIR.NET=	../network/

F.C	     	+= -W -Wall
F.I	     	+= -I./include -I$(DIR.BIND)/include -I$(DIR.THREAD)/include -I../include -I$(DIR.SFML)
F.I		+= -I$(DIR.REF)/include -I$(DIR.NET)/include -I$(DIR.PROT)/include
F.D	     	+=


all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
