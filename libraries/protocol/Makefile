##
## Makefile
##
## Made by jules baratoux
## Login   <barato_j@epitech.net>
##
## Started on  Sun May 19 02:33:10 2013 jules baratoux
## Last update Thu Feb  5 18:58:49 2015 lamber_k
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
		DeathRequest.cpp	\
		ElemRequest.cpp		\
		LooseRequest.cpp	\
		LeaveRequest.cpp	\
		VictoryRequest.cpp	\
		ChatRecvRequest.cpp	\
		ChatSendRequest.cpp	\

DIR.REF=	../Referee/

F.C	     +=	-W -Wall 
F.I	     +=	-I $(DIR.H) -I$(DIR.REF)/include
F.D	     += -Dlinux -std=c++11


all:		start $(NAME)

$(NAME):	lib_compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
