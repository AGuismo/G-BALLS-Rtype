BOT_LIBRARY=	../Server/botlibrary

all:		compile copy

compile:
		@make --no-print-directory -C ./defaultIA all
		@make --no-print-directory -C ./defaultBoss all

clean:
		@make --no-print-directory -C ./defaultIA clean
		@make --no-print-directory -C ./defaultBoss clean

fclean:
		@make --no-print-directory -C ./defaultIA fclean
		@make --no-print-directory -C ./defaultBoss fclean

copy:
		cp ./*/*.so ./$(BOT_LIBRARY)

re:		fclean all
