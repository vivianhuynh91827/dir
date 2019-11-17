dir.o: dir.c
		gcc -o program dir.c

run:
	./program

clean:
	rm program
	rm *.o
