## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libprotocol.a


SRCS =	      	ARequest.cpp		\
		AGameRequest.cpp	\
		AuthRequest.cpp		\
		SessionRequest.cpp	\
		ServerRequest.cpp	\
		PartyRequest.cpp	\
		Protocol.cpp		\
		RequestFactory.cpp	\
		AliveRequest.cpp	\
		RootRequest.cpp		\
		BuffRequest.cpp		\
		DeathRequest.cpp	\
		ElemRequest.cpp		\
		EventRequest.cpp	\
		LooseRequest.cpp	\
		LeaveRequest.cpp	\
		ScoreRequest.cpp	\
		VictoryRequest.cpp	\

DIR.BIND=	../deps/Bind
DIR.NET=	../deps/network

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I $(DIR.H) -I$(DIR.BIND)/include -I$(DIR.NET)/include -I../include
F.D	     +=


all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
