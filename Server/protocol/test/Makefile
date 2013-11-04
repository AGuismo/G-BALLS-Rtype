NAME	     ?=	requestSerializer

SRCS =	      	main.cpp		\

DIR.PROT=	../
DIR.DEPS=	../../deps/

MOD.INC=	-I$(DIR.PROT)/include

MOD.LNK=	-L$(DIR.PROT) -lprotocol

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I./include $(MOD.INC) -I../../include
F.L	     += $(MOD.LNK)
F.D	     +=

all:		start $(NAME)

$(NAME):	compile_mods compile

compile_mods:
		@$(ECHO) $(ES) "Compile Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.PROT) all F.D=$(F.D)

clean_mods:
		@$(ECHO) $(ES) "Clean Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.PROT) clean

fclean_mods:
		@$(ECHO) $(ES) "Full clean Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.PROT) fclean

clean:		remove_objects clean_mods

fclean:		clean remove_name fclean_mods

re:		fclean all

include .libmake
