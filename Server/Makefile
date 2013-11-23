NAME	     ?=	server_r-type

SRCS =	      	main.cpp		\
		Application.cpp		\
		Client.cpp		\
		RequestQueue.cpp	\
					\
		Env.cpp			\
		sys.cpp			\

DIR.GAME=	./game/
DIR.MENU=	./menu/
DIR.LOAD=	./loader/
DIR.DEPS=	./deps/
DIR.PROT=	./$(DIR.DEPS)/protocol/
DIR.DAT=	./database/

DEPS.INC=	-I$(DIR.DEPS)/network/include -I$(DIR.DEPS)/Threads/include -I$(DIR.DEPS)/Bind/include

DEPS.LNK=	-L$(DIR.DEPS)/network/ -lnetwork -L$(DIR.DEPS)/Threads/ -lThread -lpthread

MOD.INC=	-I$(DIR.GAME)/include -I$(DIR.MENU)/include -I$(DIR.LOAD)/include
MOD.INC+=	-I$(DIR.PROT)/include -I$(DIR.DAT)/include

MOD.LNK=	-L$(DIR.MENU) -lmenu -L$(DIR.GAME) -lgame -L$(DIR.LOAD) -lloader
MOD.LNK+=	-L$(DIR.PROT) -lprotocol -L$(DIR.DAT)/ -ldb

F.C	     +=	-W -Wall -Werror
F.I	     +=	$(DEPS.INC) $(MOD.INC) -I./include
F.L	     += $(DEPS.LNK) $(MOD.LNK) -Wl,-rpath=./deps
F.D	     +=

all:		start $(NAME)

$(NAME):	compile_mods compile_deps compile

compile_mods:
		@$(ECHO) $(ES) "Compile Modules" $(EE)
		@make --no-print-directory -C ./menu all F.D=$(F.D)
		@make --no-print-directory -C ./loader all F.D=$(F.D)
		@make --no-print-directory -C ./game all F.D=$(F.D)
		@make --no-print-directory -C ./$(DIR.PROT) all F.D=$(F.D)
		@make --no-print-directory -C ./$(DIR.DAT) all F.D=$(F.D)

compile_deps:
		@$(ECHO) $(ES) "Compile Dependancies" $(EE)
		@make --no-print-directory -C ./$(DIR.DEPS)/Threads/ all F.D=$(F.D)
		@make --no-print-directory -C ./$(DIR.DEPS)/network/ all F.D=$(F.D)
		@cp ./$(DIR.DEPS)/Threads/libThread.so ./$(DIR.DEPS)
		@cp ./$(DIR.DEPS)/network/libnetwork.so ./$(DIR.DEPS)

clean_mods:
		@$(ECHO) $(ES) "Clean Modules" $(EE)
		@make --no-print-directory -C ./menu clean
		@make --no-print-directory -C ./loader clean
		@make --no-print-directory -C ./game clean
		@make --no-print-directory -C ./$(DIR.PROT) clean
		@make --no-print-directory -C ./$(DIR.DAT) clean F.D=$(F.D)

clean_deps:
		@$(ECHO) $(ES) "Clean Dependancies" $(EE)
		@make --no-print-directory -C ./$(DIR.DEPS)/Threads/ clean
		@make --no-print-directory -C ./$(DIR.DEPS)/network/ clean

fclean_mods:
		@$(ECHO) $(ES) "Full clean Modules" $(EE)
		@make --no-print-directory -C ./menu fclean
		@make --no-print-directory -C ./loader fclean
		@make --no-print-directory -C ./game fclean
		@make --no-print-directory -C ./$(DIR.PROT) fclean
		@make --no-print-directory -C ./$(DIR.DAT) fclean F.D=$(F.D)

fclean_deps:
		@$(ECHO) $(ES) "Full clean Dependancies" $(EE)
		@make --no-print-directory -C ./$(DIR.DEPS)/Threads/ fclean
		@make --no-print-directory -C ./$(DIR.DEPS)/network/ fclean
		@rm -f ./$(DIR.DEPS)/libThread.so
		@rm -f ./$(DIR.DEPS)/libnetwork.so

clean:		remove_objects clean_mods clean_deps

fclean:		clean remove_name fclean_mods fclean_deps

re:		fclean all

include .libmake
