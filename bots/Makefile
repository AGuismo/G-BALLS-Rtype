all:		start $(NAME)

$(NAME):	compile_mods compile_deps compile

compile:
		@make --no-print-directory -C ./defaultIA all F.L=$(F.L)

clean:
		@make --no-print-directory -C ./defaultIA clean

fclean:
		@make --no-print-directory -C ./defaultIA fclean

re:		fclean all

include .libmake
