## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘

ProjectDir=	./FileListing
ProjectName=	"FileListing"

all:		release

release:
		$(ECHO) $(ES) "Compile $(ProjectName) in Release mode..." $(EE)
		@make --no-print-directory -C ./$(ProjectDir) F.D+=" -DNDEBUG"

debug:
		$(ECHO) $(ES) "Compile $(ProjectName) in Debug mode..." $(EE)
		@make --no-print-directory -C ./$(ProjectDir) F.D+=" -g3 -DDEBUG"

compileTests:	test1

test1:		debug
		g++ ./tests/test1.cpp -I./$(ProjectDir)/include -L./$(ProjectDir) -l$(ProjectName) -Wl,-rpath=./$(ProjectDir)

clean:
		@make --no-print-directory -C ./$(ProjectDir) clean

fclean:
		@make --no-print-directory -C ./$(ProjectDir) fclean

re:		fclean all




include .libmake
