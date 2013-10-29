## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libThread.so

DIR.DEPS=	./deps/

DIR.BIND=	./Bind/

SRCS =	      	ThreadCond.cpp	\
		ThreadMutex.cpp	\

F.C	     +=	-W -Wall -Werror -fPIC
F.I	     +=	-I $(DIR.H) -I./$(DIR.DEPS)/$(DIR.BIND)/include
F.L	     += -lpthread -shared
F.D	     += -DNDEBUG


all:		start $(NAME)

$(NAME):	compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
