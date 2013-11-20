## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libdb.a

THREAD.DIR	=	../deps/Threads
PROTOCOL.DIR	=	../protocol

SRCS =	      	Backup.cpp		\
		MD5.cpp			\
		Database.cpp		\
		Salt.cpp

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I $(DIR.H) -I$(THREAD.DIR)/include -I$(PROTOCOL.DIR)/include -I../include
F.D	     +=

all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
