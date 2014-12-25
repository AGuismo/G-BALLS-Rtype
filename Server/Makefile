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
DIR.NET=	./$(DIR.DEPS)/network/
DIR.THREAD=	./$(DIR.DEPS)/Threads/
DIR.DAT=	./database/
DIR.IAAPI=	./../bots/API

DEPS.INC=	-I$(DIR.DEPS)/network/include -I$(DIR.DEPS)/Threads/include -I$(DIR.DEPS)/Bind/include
DEPS.INC+=	-I$(DIR.IAAPI)/include

DEPS.LNK=	-L$(DIR.NET) -lnetwork -L$(DIR.THREAD) -lThread -lpthread -ldl

MOD.INC=	-I$(DIR.GAME)/include -I$(DIR.MENU)/include -I$(DIR.LOAD)/include
MOD.INC+=	-I$(DIR.PROT)/include -I$(DIR.DAT)/include

MOD.LNK=	-L$(DIR.MENU) -lmenu -L$(DIR.GAME) -lgame -L$(DIR.LOAD) -lloader
MOD.LNK+=	-L$(DIR.PROT) -lprotocol -L$(DIR.DAT)/ -ldb

F.C	     +=	-W -Wall -Werror
F.I	     += $(MOD.INC) $(DEPS.INC) -I./include
F.L	     += $(MOD.LNK) $(DEPS.LNK) -Wl,-rpath=./deps
F.D	     +=

all:		start $(NAME)

$(NAME):	compile_mods compile_deps compile

compile_mods:
		@$(ECHO) $(ES) "Compile Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.MENU) all F.D=$(F.D)
		@make --no-print-directory -C ./$(DIR.LOAD) all F.D=$(F.D)
		@make --no-print-directory -C ./$(DIR.GAME) all F.D=$(F.D)
		@make --no-print-directory -C ./$(DIR.PROT) all F.D=$(F.D)
		@make --no-print-directory -C ./$(DIR.DAT) all F.D=$(F.D)

compile_deps:
		@$(ECHO) $(ES) "Compile Dependancies" $(EE)
		@make --no-print-directory -C ./$(DIR.THREAD) all F.D=$(F.D)
		@make --no-print-directory -C ./$(DIR.NET) all F.D=$(F.D)
		@cp ./$(DIR.THREAD)/libThread.so ./$(DIR.DEPS)
		@cp ./$(DIR.NET)/libnetwork.so ./$(DIR.DEPS)

clean_mods:
		@$(ECHO) $(ES) "Clean Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.MENU) clean
		@make --no-print-directory -C ./$(DIR.LOAD) clean
		@make --no-print-directory -C ./$(DIR.GAME) clean
		@make --no-print-directory -C ./$(DIR.PROT) clean
		@make --no-print-directory -C ./$(DIR.DAT) clean

clean_deps:
		@$(ECHO) $(ES) "Clean Dependancies" $(EE)
		@make --no-print-directory -C ./$(DIR.THREAD) clean
		@make --no-print-directory -C ./$(DIR.NET) clean

fclean_mods:
		@$(ECHO) $(ES) "Full clean Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.MENU) fclean
		@make --no-print-directory -C ./$(DIR.LOAD) fclean
		@make --no-print-directory -C ./$(DIR.GAME) fclean
		@make --no-print-directory -C ./$(DIR.PROT) fclean
		@make --no-print-directory -C ./$(DIR.DAT) fclean

fclean_deps:
		@$(ECHO) $(ES) "Full clean Dependancies" $(EE)
		@make --no-print-directory -C ./$(DIR.THREAD) fclean
		@make --no-print-directory -C ./$(DIR.NET) fclean
		@rm -f ./$(DIR.DEPS)/libThread.so
		@rm -f ./$(DIR.DEPS)/libnetwork.so

clean:		remove_objects clean_mods clean_deps

fclean:		clean remove_name fclean_mods fclean_deps

re:		fclean all

include .libmake
