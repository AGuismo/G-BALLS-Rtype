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
		TextureManager.cpp

DEPS.INC=	

DEPS.LNK=	

MOD.INC=	

MOD.LNK=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

F.C	     +=	-W -Wall -Werror
F.I	     +=	$(DEPS.INC) $(MOD.INC) -I./include
F.L	     += $(DEPS.LNK) $(MOD.LNK)
F.D	     +=

all:		start $(NAME)

$(NAME):	compile_mods compile_deps compile

compile_mods:
		@$(ECHO) $(ES) "Compile Modules" $(EE)

compile_deps:
		@$(ECHO) $(ES) "Compile Dependancies" $(EE)

clean_mods:
		@$(ECHO) $(ES) "Clean Modules" $(EE)

clean_deps:
		@$(ECHO) $(ES) "Clean Dependancies" $(EE)

fclean_mods:
		@$(ECHO) $(ES) "Full clean Modules" $(EE)

fclean_deps:
		@$(ECHO) $(ES) "Full clean Dependancies" $(EE)

clean:		remove_objects clean_mods clean_deps

fclean:		clean remove_name fclean_mods fclean_deps

re:		fclean all

include .libmake
