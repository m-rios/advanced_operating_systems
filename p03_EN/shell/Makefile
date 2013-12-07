uShell: main.o commands.o parser.o
	gcc -Wall main.o commands.o parser.o -o uShell

main.o: main.c
	gcc -c -Wall main.c -o main.o

commands.o: commands.c
	gcc -c -Wall commands.c -o commands.o

parser.o: parser.c
	gcc -c -Wall parser.c -o parser.o