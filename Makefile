SHELL = /bin/sh
CC=g++
CFLAGS= 
CPPFLAGS= -O3
LDFLAGS= -O3

.SUFFIXES:
.SUFFIXES: .cpp .c .o

all: FYP

fyp: FYP

FYP: utils.o main.o aes.o input-ctr.o input-ecb.o core.o aes256.o 
	$(CC) utils.o main.o aes.o input-ctr.o input-ecb.o core.o aes256.o -o FYP 

core.o: utils.o

aes.o: input-ctr.o input-ecb.o aes256.o utils.o

input-ctr.o: aes.o utils.o

input-ecb.o: aes.o utils.o

.PHONY: all clean

clean:
	rm -rf main.o utils.o aes.o vector.o input-ctr.o input-ecb.o core.o aes256.o


