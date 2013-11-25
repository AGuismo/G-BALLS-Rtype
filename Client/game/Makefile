## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libgame.a

SRCS =	      	Animation.cpp		\
		AObject.cpp		\
		AudioManager.cpp	\
		Bang.cpp		\
		Bydos1.cpp		\
		BydosPlasma.cpp		\
		IndestructibleWall.cpp	\
		DestructibleWall.cpp	\
		BydosLaser.cpp		\
		GarbageBoss.cpp		\
		ShrimpBoss.cpp		\
		Factory.cpp		\
		Game.cpp		\
		GameWindow.cpp		\
		Layer.cpp		\
		LayerManager.cpp	\
		TextureManager.cpp	\
		Player.cpp		\
		PlayerLaser.cpp		\
		PlayerBlast.cpp		\
		ZogZog.cpp		\
		Timer.cpp		\
		Slider.cpp		\

DIR.THREAD=	../../libraries/Thread/Threads
DIR.BIND=	../../libraries/Bind
DIR.PROT=	../../libraries/protocol
DIR.NET=	../network/

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I $(DIR.H) -I$(DIR.BIND)/include -I$(DIR.THREAD)/include -I../include -I$(DIR.NET)/include -I$(DIR.PROT)/include
F.D	     +=


all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
