CORE_C = core/cd.c core/echo.c core/exe.c core/fg.c core/history.c core/jobs.c core/ls.c core/pinfo.c core/pwd.c core/replay.c core/sig.c
UTILS_C = utils/execute.c utils/input.c utils/pipe.c utils/printdr.c utils/recenthistory.c utils/redirect.c utils/sep.c utils/trim.c

H_FILES = global.h
ARGS = -lreadline -I .
EXE = fresh

all:
	gcc -o $(EXE) main.c $(CORE_C) $(UTILS_C) $(ARGS) && clear && ./$(EXE)

run: $(EXE)
	clear
	./$(EXE)

build :  main.c $(CORE_C) $(UTILS_C) $(H_FILES)
	gcc -o $(EXE) main.c $(CORE_C) $(UTILS_C) $(ARGS)