## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libloader.a


SRCS =	      	LoaderManager.cpp	\
		LoaderException.cpp	\
		CheckFileAbstract.cpp	\
		DynamicAbstract.cpp	\

DIR.DEPS=	../../libraries/
DIR.THREADS=	./$(DIR.DEPS)/Thread/Threads
DIR.BIND=	./$(DIR.DEPS)/Bind
DIR.PROTO=	./$(DIR.DEPS)/protocol
DIR.IAAPI=	../../bots/API/

F.C	     +=	-W -Wall 
F.I	     +=	-I $(DIR.H) -I$(DIR.BIND)/include -I$(DIR.PROTO)/include -I$(DIR.THREADS)/include
F.I	     += -I../include -I$(DIR.IAAPI)
F.D	     +=


all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
