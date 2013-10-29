## ┌───────────────────────────────────────────────────────────────────────────┐
## │                                MAKEFILE                                   │
## └───────────────────────────────────────────────────────────────────────────┘



all:		release

release:
		$(ECHO) $(ES) "Compile Thread in Release mode..." $(EE) 
		@make --no-print-directory -C ./Threads F.D+=" -DNDEBUG"

debug:
		$(ECHO) $(ES) "Compile Thread in Debug mode..." $(EE)
		@make --no-print-directory -C ./Threads F.D+=" -g3 -DDEBUG"

testEvent:	debug
		$(ECHO) $(ES) "Compile Event test..." $(EE)
		@make --no-print-directory -C ./tests testEvent

testConsumer:	debug
		$(ECHO) $(ES) "Compile Consumer test..." $(EE)
		@make --no-print-directory -C ./tests testConsumer

testThreadPool:	debug
		$(ECHO) $(ES) "Compile ThreadPool test..." $(EE)
		@make --no-print-directory -C ./tests testThreadPool

compileTests:	testEvent testConsumer testThreadPool

clean:
		@make --no-print-directory -C ./Threads fclean
		@make --no-print-directory -C ./tests clean






include .libmake
