CC=gcc
CFLAGS=-s -lcrypto

all: clean build

default: build

build: server.c client.c transport.c io.c security.c sec.c gen_cert.c 
	${CC} -o server server.c transport.c io.c security.c sec.c ${CFLAGS}
	${CC} -o client client.c transport.c io.c security.c sec.c ${CFLAGS}
	${CC} -o gen_cert gen_cert.c security.c ${CFLAGS}

clean:
	rm -rf server client *.bin *.out *.dSYM

zip: clean
	rm -f project.zip
	mkdir -p project
	cp server.c client.c transport.c io.c security.c sec.c transport.h io.h consts.h security.h sec.h Makefile project
	zip project1.zip project/*
