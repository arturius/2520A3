CFLAGS = -Wall -std=c99 -pedantic -Iinclude

all: question1 question2

question1: src/q1.c include/A3.h 
	gcc $(CFLAGS) src/q1.c -o bin/q1 

question2: src/q2.c include/A3.h
	gcc $(CFLAGS) src/q2.c -o bin/q2 

clean: 
	rm -rf bin/q1 bin/q2

