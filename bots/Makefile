F.C	     +=	-W -Wall -Werror -fPIC
F.I	     += -I../API
F.D	     += -shared

all:		start $(NAME)

$(NAME):	compile_mods compile_deps compile

compile:
		@make --no-print-directory -C ./defaultIA all F.D=$(F.D) F.I=$(F.I) F.D=$(F.D)

clean:
		@make --no-print-directory -C ./defaultIA clean

fclean:
		@make --no-print-directory -C ./defaultIA fclean

re:		fclean all

include .libmake
