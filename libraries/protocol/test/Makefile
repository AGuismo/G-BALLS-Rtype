NAME	     ?=	protocolTest

SRCS =	      	AGameRequestTest.cpp	\
		AuthRequestTest.cpp	\
		ChatRecvRequestTest.cpp	\
		ChatSendRequestTest.cpp	\
		DeathRequestTest.cpp	\
		ElemRequestTest.cpp	\

DIR.PROT=	../
DIR.REF=	../../Referee/

MOD.INC=	-I$(DIR.PROT)/include -I$(DIR.REF)/include

MOD.LNK=	-L$(DIR.PROT) -lprotocol -L$(DIR.REF) -lReferee -lpthread -lgtest -lgtest_main

F.C	     +=	-W -Wall
F.I	     +=	$(MOD.INC)
F.L	     += $(MOD.LNK)
F.D	     += -Dlinux

all:		start $(NAME)

$(NAME):	compile_mods compile

compile_mods:
		@$(ECHO) $(ES) "Compile Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.PROT) all F.D=$(F.D)
		@make --no-print-directory -C ./$(DIR.REF) all F.D=$(F.D)

clean_mods:
		@$(ECHO) $(ES) "Clean Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.PROT) clean
		@make --no-print-directory -C ./$(DIR.REF) clean

fclean_mods:
		@$(ECHO) $(ES) "Full clean Modules" $(EE)
		@make --no-print-directory -C ./$(DIR.PROT) fclean
		@make --no-print-directory -C ./$(DIR.REF) fclean

clean:		remove_objects clean_mods

fclean:		clean remove_name fclean_mods

re:		fclean all

include .libmake
