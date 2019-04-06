build:
	gcc src/c/*.c -o bin/game.exe

debug:
	gcc src/c/*.c -o bin/game_debug.exe

run:
	gcc src/c/*.c -o bin/game.exe
	./bin/game.exe
