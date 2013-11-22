NAME	     ?=	G-BALLS

SRCS =	      	main.cpp		\
		AScreen.cpp		\
		Application.cpp		\
		AWidget.cpp		\
		Background.cpp		\
		Button.cpp		\
		CheckBox.cpp		\
		Image.cpp		\
		Interface.cpp		\
		LineServer.cpp		\
		MenuWindow.cpp		\
		Network.cpp		\
		TextArea.cpp		\
		TextBlock.cpp		\
		Text.cpp		\
		Texture.cpp		\
		TextureManager.cpp	\
		InfosUser.cpp		\

DIR.THREAD=	../libraries/Thread/Threads
DIR.BIND=	../libraries/Bind
DIR.NETWORK=	./network/
DIR.GAME=	./game/

DEPS.INC=	-I$(DIR.BIND)/include -I$(DIR.THREAD)/include -I$(DIR.GAME)/include

DEPS.LNK=	-lsfml-graphics -lsfml-window -lsfml-system  -lsfml-network -lsfml-audio
DEPS.LNK+=	-L$(DIR.THREAD) -lThread -lpthread

MOD.INC=	-I$(DIR.NETWORK)/include

MOD.LNK=	-L$(DIR.NETWORK) -lnetwork -L$(DIR.GAME) -lgame

F.C	     +=	-W -Wall -Werror
F.I	     +=	$(DEPS.INC) $(MOD.INC) -I./include
F.L	     += $(MOD.LNK) $(DEPS.LNK)
F.D	     +=

all:		start $(NAME)

$(NAME):	compile_mods compile_deps compile

compile_mods:
		@$(ECHO) $(ES) "Compile Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.NETWORK) all F.D=$(F.D)
		@make --no-print-directory -C ./$(DIR.GAME) all F.D=$(F.D)

compile_deps:
		@$(ECHO) $(ES) "Compile Dependancies" $(EE)
		@make --no-print-directory -C ./$(DIR.THREAD) all F.D=$(F.D)

clean_mods:
		@$(ECHO) $(ES) "Clean Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.NETWORK) clean
		@make --no-print-directory -C ./$(DIR.GAME) clean

clean_deps:
		@$(ECHO) $(ES) "Clean Dependancies" $(EE)
		@make --no-print-directory -C ./$(DIR.THREAD) clean

fclean_mods:
		@$(ECHO) $(ES) "Full clean Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.NETWORK) fclean
		@make --no-print-directory -C ./$(DIR.GAME) fclean

fclean_deps:
		@$(ECHO) $(ES) "Full clean Dependancies" $(EE)
		@make --no-print-directory -C ./$(DIR.THREAD) fclean

clean:		remove_objects clean_mods clean_deps

fclean:		clean remove_name fclean_mods fclean_deps

re:		fclean all

include .libmake
