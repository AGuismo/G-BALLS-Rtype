##
## Makefile for rtype in /home/brigno/Projects/R-Type/r-type/Client
##
## Made by brigno
## Login   <brigno@epitech.net>
##
## Started on  Wed Oct 23 18:43:59 2013 brigno
## Last update Wed Nov  6 01:43:52 2013 brigno
##

NAME	=	Client

SOURCES =	Sources/

SRC =		main.cpp			\
		$(SOURCES)Application.cpp	\
		$(SOURCES)Background.cpp	\
		$(SOURCES)MenuWindow.cpp	\
		$(SOURCES)Text.cpp		\
		$(SOURCES)AWidget.cpp		\
		$(SOURCES)Image.cpp		\
		$(SOURCES)TextArea.cpp		\
		$(SOURCES)Button.cpp		\
		$(SOURCES)Interface.cpp		\
		$(SOURCES)Network.cpp		\
		$(SOURCES)AScreen.cpp		\
		$(SOURCES)Texture.cpp		\
		$(SOURCES)TextureManager.cpp	\

OBJ =		$(SRC:.cpp=.o)
CC =		g++
INCLUDE =	-I./Includes
CXXFLAGS +=	$(INCLUDE)
CXXFLAGS +=	-W -Wall -Wextra -ansi -pedantic
CFLAGS +=	$(INCLUDE)
CFLAGS +=	-W -Wall -Wextra -ansi -pedantic
LFLAGS =	-L../Server/protocol/ -lprotocol -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
RM =		rm -f
ECHO =		echo -e

$(NAME):	$(OBJ)
		@$(CC) -o $(NAME) $(OBJ) $(LFLAGS)
		@$(ECHO) '\033[0;32m> Compiled\033[0m'

clean:
		-@$(RM) $(OBJ)
		-@$(RM) *~
		-@$(RM) *#
		@$(ECHO) '\033[0;35m> Directory cleaned\033[0m'

all:		$(NAME)

fclean:		clean
		-@$(RM) $(NAME)
		@$(ECHO) '\033[0;35m> Remove executable\033[0m'

re:		fclean all

.PHONY:		all fclean clean re
