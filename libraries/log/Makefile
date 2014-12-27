## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	liblog.so


SRCS =	      	Log.cpp		\
		Debug.cpp

F.C	     +=	-W -Wall  -fPIC
F.I	     +=	-I $(DIR.H)
F.L	     += -shared
F.D	     += -DNDEBUG


all:		start $(NAME)

$(NAME):	compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
