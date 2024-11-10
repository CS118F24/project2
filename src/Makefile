CC=gcc
CFLAGS=-s

all: clean build

default: build

build: server.c client.c transport.c io.c 
	${CC} -o server server.c transport.c io.c ${CFLAGS}
	${CC} -o client client.c transport.c io.c ${CFLAGS}

clean:
	rm -rf server client *.bin *.out *.dSYM

zip: clean
	rm -f project.zip
	mkdir -p project
	cp server.c client.c transport.c io.c transport.h io.h consts.h Makefile project
	zip project1.zip project/*
