EXE_PATH = bin/game.exe

MAIN = src/c/main.c
SOURCES = $(shell find . -mindepth 4 -name "*.c" ) ${MAIN}
COMPILE_CMD = gcc ${SOURCES} -o ${EXE_PATH}
RUN_CMD = ./${EXE_PATH}

build:
	$(COMPILE_CMD)

run:
	$(COMPILE_CMD)
	$(RUN_CMD)
