## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libloader.a


SRCS =	      	LoaderManager.cpp	\
		LoaderException.cpp	\

DIR.THREADS=	../deps/Threads
DIR.BIND=	../deps/Bind

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I $(DIR.H) -I$(DIR.BIND)/include -I$(DIR.THREADS)/include
F.D	     +=


all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
