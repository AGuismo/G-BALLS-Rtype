NAME	     ?=	defaultBoss.so

SRCS =	      	DefaultBoss.cpp		\

F.C	     += -W -Wall -Werror -fPIC
F.I	     += -I./include -I../API
F.L	     += -shared

all:		start $(NAME)

$(NAME):	compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all

include .libmake
