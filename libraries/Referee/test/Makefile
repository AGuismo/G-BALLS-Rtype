##
## Makefile
##
## Made by jules baratoux
## Login   <barato_j@epitech.net>
##
## Started on  Sun May 19 02:33:10 2013 jules baratoux
## Last update Thu Feb  5 17:27:29 2015 lamber_k
##
## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



NAME	     ?=	RefereeTest

SRCS	      =	RefereeClientTest.cpp	\
		RefereeServerTest.cpp	\

DIR.DEPS=	./../../
DIR.PROT=	$(DIR.DEPS)/protocol/
DIR.REF=	../

F.C          +=	-W -Wextra -Wall -std=c++11
F.C          += 
F.L          += -L$(DIR.PROT) -lprotocol -L$(DIR.REF) -lReferee -lgtest -lgtest_main -lpthread
F.I	     += -I$(DIR.PROT)/include -I$(DIR.REF)/include
F.D	     += -DNDEBUG -Dlinux





all:		start $(NAME)

$(NAME):	compile_mods compile

compile_mods:
		make --no-print-directory -C ./$(DIR.PROT) all F.D="$(F.D)"
		@make --no-print-directory -C ./$(DIR.REF) all F.D="$(F.D)"

clean:		clean_mods remove_objects

clean_mods:
		@make --no-print-directory -C ./$(DIR.PROT) clean
		@make --no-print-directory -C ./$(DIR.REF) clean

fclean:		fclean_mods clean remove_name

fclean_mods:
		@make --no-print-directory -C ./$(DIR.PROT) fclean
		@make --no-print-directory -C ./$(DIR.REF) fclean

re:		fclean all



























































include .libmake
