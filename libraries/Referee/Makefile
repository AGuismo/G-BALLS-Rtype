##
## Makefile
##
## Made by jules baratoux
## Login   <barato_j@epitech.net>
##
## Started on  Sun May 19 02:33:10 2013 jules baratoux
## Last update Thu Feb  5 22:04:00 2015 lamber_k
##
## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libReferee.a

LD	      =	ar rcs

SRCS	      =	Clock.cpp		\
		Entity.cpp		\
		EntityFactory.cpp	\
		ObjectMoverFactory.cpp	\
		Missile.cpp		\
		Mob.cpp			\
		ObjectMover.cpp		\
		ObjectMoverStraight.cpp	\
		Player.cpp		\
		Position.cpp		\
		GameMap.cpp		\
		RefereeClient.cpp	\
		Scenario.cpp		\
		Time.cpp

DIR.DEPS=	./../
DIR.PROT=	$(DIR.DEPS)/protocol/


F.C          +=	-W -Wextra -Wall -std=c++11
F.C          += 
F.L          +=
F.I	     += -I$(DIR.PROT)/include
F.D	     += -DNDEBUG -Dlinux





all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all



























































include .libmake
