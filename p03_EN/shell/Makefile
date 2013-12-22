uShell: main.o commands.o parser.o auxFunc.o
	gcc -Wall main.o commands.o parser.o auxFunc.o -o uShell

main.o: main.c
	gcc -c -Wall main.c -o main.o

auxFunc.o: auxFunc.c auxFunc.h
	gcc -c -Wall auxFunc.c -o auxFunc.o

commands.o: commands.c commands.h
	gcc -c -Wall commands.c -o commands.o

parser.o: parser.c
	gcc -c -Wall parser.c -o parser.o

clean:
	rm -f *.o
	rm -f uShell
	rm -f test