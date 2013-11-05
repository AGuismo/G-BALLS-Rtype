NAME	     ?=	requestSerializer

SRCS =	      	main.cpp		\

DIR.PROT=	../
DIR.NET=	$(DIR.DEPS)/network/
DIR.DEPS=	../../deps/

DEPS.INC=	-I$(DIR.NET)/include

MOD.INC=	-I$(DIR.PROT)/include

DEPS.LNK=	-L$(DIR.NET) -lnetwork

MOD.LNK=	-L$(DIR.PROT) -lprotocol

F.C	     +=	-W -Wall -Werror
F.I	     +=	-I./include $(MOD.INC) -I../../include $(DEPS.INC)
F.L	     += $(MOD.LNK) $(DEPS.LNK) -Wl,-rpath=$(DIR.NET)
F.D	     +=

all:		start $(NAME)

$(NAME):	compile_mods compile

compile_mods:
		@$(ECHO) $(ES) "Compile Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.PROT) all F.D=$(F.D)
		@make --no-print-directory -C ./$(DIR.NET) all F.D=$(F.D)

clean_mods:
		@$(ECHO) $(ES) "Clean Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.PROT) clean
		@make --no-print-directory -C ./$(DIR.NET) clean

fclean_mods:
		@$(ECHO) $(ES) "Full clean Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.PROT) fclean
		@make --no-print-directory -C ./$(DIR.NET) fclean

clean:		remove_objects clean_mods

fclean:		clean remove_name fclean_mods

re:		fclean all

include .libmake
