##
## Makefile
##
## Made by jules baratoux
## Login   <barato_j@epitech.net>
##
## Started on  Sun May 19 02:33:10 2013 jules baratoux
## Last update Fri Jan 23 18:27:11 2015 lamber_k
##
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
		NextStage.cpp		\
		LooseRequest.cpp	\
		LeaveRequest.cpp	\
		ScoreRequest.cpp	\
		VictoryRequest.cpp	\
		ChatRecvRequest.cpp	\
		ChatSendRequest.cpp	\

# DIR.BIND=	../deps/Bind
# DIR.NET=	../deps/network
DIR.REF=	../Referee/

F.C	     +=	-W -Wall 
F.I	     +=	-I $(DIR.H) -I$(DIR.REF)/include
F.D	     +=


all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
