NAME	     ?=	server_r-type

SRCS =	      	main.cpp	\
		Application.cpp	\
				\
		sys.cpp		\

DIR.GAME=	./game/
DIR.MENU=	./menu/
DIR.LOAD=	./loader/
DIR.DEPS=	./deps/

DEPS.INC=	-I$(DIR.DEPS)/Threads/include

DEPS.LNK=	-L$(DIR.DEPS)/Threads/ -lThread -lpthread

MOD.INC=	-I$(DIR.GAME)/include -I$(DIR.MENU)/include -I$(DIR.LOAD)/include

MOD.LNK=	-L$(DIR.GAME) -lgame -L$(DIR.MENU) -lmenu -L$(DIR.LOAD) -lloader

F.C	     +=	-W -Wall -Werror
F.I	     +=	$(DEPS.INC) $(MOD.INC)
F.L	     += $(DEPS.LNK) $(MOD.LNK)
F.D	     += 

all:		start $(NAME)

$(NAME):	compile_mods compile_deps compile

compile_mods:
		@$(ECHO) $(ES) "Compile Modules" $(EE)
		@make --no-print-directory -C ./menu all F.D=$(F.D)
		@make --no-print-directory -C ./loader all F.D=$(F.D)
		@make --no-print-directory -C ./game all F.D=$(F.D)

compile_deps:
		@$(ECHO) $(ES) "Compile Dependancies" $(EE)
		@make --no-print-directory -C ./deps/Threads/ all F.D=$(F.D)

clean_mods:
		@$(ECHO) $(ES) "Clean Modules" $(EE)
		@make --no-print-directory -C ./menu clean
		@make --no-print-directory -C ./loader clean
		@make --no-print-directory -C ./game clean

clean_deps:
		@$(ECHO) $(ES) "Clean Dependancies" $(EE)
		@make --no-print-directory -C ./deps/Threads/ clean

fclean_mods:
		@$(ECHO) $(ES) "Full clean Modules" $(EE)
		@make --no-print-directory -C ./menu fclean
		@make --no-print-directory -C ./loader fclean
		@make --no-print-directory -C ./game fclean

fclean_deps:
		@$(ECHO) $(ES) "Full clean Dependancies" $(EE)
		@make --no-print-directory -C ./deps/Threads/ fclean

clean:		remove_objects clean_mods clean_deps

fclean:		clean remove_name fclean_mods fclean_deps

re:		fclean all

include .libmake
