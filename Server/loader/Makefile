## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libloader.a


SRCS =	      	LoaderManager.cpp	\
		LoaderException.cpp	\
		CheckFileAbstract.cpp	\
		DynamicAbstract.cpp	\

DIR.DEPS=	../../libraries/
DIR.LOG=	./$(DIR.DEPS)/log
DIR.THREADS=	./$(DIR.DEPS)/Thread/Threads
DIR.BIND=	./$(DIR.DEPS)/Bind
DIR.PROTO=	./$(DIR.DEPS)/protocol
DIR.IAAPI=	../../bots/API/

F.C	     +=	-W -Wall 
F.I	     +=	-I $(DIR.H) -I$(DIR.BIND)/include -I$(DIR.PROTO)/include
F.I	     += -I$(DIR.THREADS)/include -I$(DIR.LOG)/include
F.I	     += -I../include -I$(DIR.IAAPI)
F.D	     +=


all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
