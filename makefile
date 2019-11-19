ifeq ($(DEBUG),true)
	CC = gcc -g
else
	CC = gcc
endif

dir.o: dir.c dir.h
	$(CC) -o program dir.c

run:
	./program

clean:
	rm program
	rm *.o
