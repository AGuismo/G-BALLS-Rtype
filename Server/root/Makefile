NAME	     ?=	root

SRCS =	      	main.cpp		\

DIR.DEPS=	./../../libraries/
DIR.PROT=	$(DIR.DEPS)/protocol/
DIR.NET=	$(DIR.DEPS)/network/network/
DIR.DB=		../database/

DEPS.INC=	-I$(DIR.NET)/include

MOD.INC=	-I$(DIR.PROT)/include -I$(DIR.DB)/include

DEPS.LNK=	-L$(DIR.NET) -lnetwork

MOD.LNK=	-L$(DIR.PROT) -lprotocol -L$(DIR.DB) -ldb

F.C	     +=	-W -Wall 
F.I	     += $(MOD.INC) $(DEPS.INC) -I./include
F.L	     += $(MOD.LNK) $(DEPS.LNK) -Wl,-rpath=$(DIR.DEPS)
F.D	     +=

all:		start $(NAME)

$(NAME):	compile_mods compile_deps compile

compile_mods:
		@$(ECHO) $(ES) "Compile Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.PROT) all F.D=$(F.D)

compile_deps:
		@$(ECHO) $(ES) "Compile Dependancies" $(EE)
		@make --no-print-directory -C ./$(DIR.NET) all F.D=$(F.D)

clean_mods:
		@$(ECHO) $(ES) "Clean Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.PROT) clean

clean_deps:
		@$(ECHO) $(ES) "Clean Dependancies" $(EE)
		@make --no-print-directory -C ./$(DIR.NET) clean

fclean_mods:
		@$(ECHO) $(ES) "Full clean Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.PROT) fclean

fclean_deps:
		@$(ECHO) $(ES) "Full clean Dependancies" $(EE)
		@make --no-print-directory -C ./$(DIR.NET) fclean

clean:		remove_objects clean_mods clean_deps

fclean:		clean remove_name fclean_mods fclean_deps

re:		fclean all

include .libmake
