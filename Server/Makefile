NAME	     ?=	server_r-type

SRCS =	      	main.cpp	\
		Application.cpp	\

F.C	     +=	-W -Wall -Werror
F.I	     +=	
F.L	     += 
F.D	     += 

all:		start $(NAME)

$(NAME):	compile_deps compile

compile_deps:
		@make --no-print-directory -C ./menu all F.D=$(F.D)
		@make --no-print-directory -C ./loader all F.D=$(F.D)
		@make --no-print-directory -C ./game all F.D=$(F.D)
		@make --no-print-directory -C ./deps/Threads/ all F.D=$(F.D)

clean_deps:
		@make --no-print-directory -C ./menu clean
		@make --no-print-directory -C ./loader clean
		@make --no-print-directory -C ./game clean
		@make --no-print-directory -C ./deps/Threads/ clean

fclean_deps:
		@make --no-print-directory -C ./menu fclean
		@make --no-print-directory -C ./loader fclean
		@make --no-print-directory -C ./game fclean
		@make --no-print-directory -C ./deps/Threads/ fclean

clean:		remove_objects clean_deps

fclean:		clean remove_name fclean_deps

re:		fclean all

include .libmake
