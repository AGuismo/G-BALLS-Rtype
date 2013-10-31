## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	libnetwork.so

SRCS =	      	AMonitorable.cpp	\
		cBuffer.cpp		\
		ClientAccepted.cpp	\
		streamManager.cpp	\
		TcpClient.cpp		\
		TcpServer.cpp		\
		UdpClient.cpp		\
		UdpServer.cpp		\

F.C	     +=	-W -Wall -Werror -fPIC
F.I	     +=	-I $(DIR.H)
F.L	     += -shared
F.D	     += -DNDEBUG


all:		start $(NAME)

$(NAME):	compile

clean:		remove_objects

fclean:		clean remove_name

re:		fclean all























































include .libmake
