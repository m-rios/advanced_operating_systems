count: main.o libcount.a
	gcc -Wall -g main.o libcount.a -o count

main.o: main.c
	gcc -c -g -Wall main.c -o main.o

libcount.a: readchar_R.o count_M.o
	ar -r libcount.a readchar_R.o count_M.o libcount.a

readchar_R.o: readchar_R.c
	gcc -c -g -Wall readchar_R.c -o readchar_R.o

count_M.o: count_M.c
	gcc -c -g -Wall count_M.c -o count_M.o

clean:
	rm -f *.o
	rm -f count
	rm -f *.a