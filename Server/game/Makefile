## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libgame.a


SRCS =	      	GameManager.cpp		\
		GameException.cpp	\

DIR.THREADS=	../deps/Threads

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I $(DIR.H) -I$(DIR.THREADS)/include
F.D	     +=

all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
