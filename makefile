CORE_C = core/cd.c core/echo.c core/execvp.c core/history.c core/ls.c core/pinfo.c core/pwd.c
UTILS_C = utils/command_executor.c utils/command_separator.c utils/input.c utils/dir.c

H_FILES = global.h
ARGS = -lreadline -I .
EXE = fresh

run: $(EXE)
	clear
	./$(EXE)

build :  main.c $(CORE_C) $(UTILS_C) $(H_FILES)
	gcc -o fresh main.c $(CORE_C) $(UTILS_C) $(ARGS)
