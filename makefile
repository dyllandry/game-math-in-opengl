CC=gcc

main: src/main.o src/opengl-api.o
	$(CC) -o bin/main src/main.o src/opengl-api.o -lglfw -lGL -fPIC -ldl

