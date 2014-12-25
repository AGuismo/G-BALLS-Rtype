## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘

ProjectDir=	./MDynamic
ProjectName=	"MDynamic"

all:		release

release:
		$(ECHO) $(ES) "Compile $(ProjectName) in Release mode..." $(EE)
		@make --no-print-directory -C ./$(ProjectDir) F.D+=" -DNDEBUG"

debug:
		$(ECHO) $(ES) "Compile $(ProjectName) in Debug mode..." $(EE)
		@make --no-print-directory -C ./$(ProjectDir) F.D+=" -g3 -DDEBUG"

compileTests:	testlibrary test1

testlibrary:
		@make --no-print-directory -C ./tests/myLibrary F.D+=" -g3 -DDEBUG"

test1:		testlibrary debug
		cp ./tests/myLibrary/libmyLibrary.so .
		g++ ./tests/main.cpp -I./$(ProjectDir)/include -I./tests/myLibrary/include  -L. -Wl,-rpath=. -lmyLibrary -L./$(ProjectDir) -l$(ProjectName) -ldl

clean:
		@make --no-print-directory -C ./$(ProjectDir) clean
		rm -f libmyLibrary.so

fclean:
		@make --no-print-directory -C ./$(ProjectDir) fclean

re:		fclean all




include .libmake
