build:
	gcc src/c/game/*.c src/c/main.c -o bin/game.exe

debug:
	gcc src/c/game/*.c src/c/main.c -o bin/game_debug.exe

run:
	gcc src/c/game/*.c src/c/main.c -o bin/game.exe
	./bin/game.exe
