count: main.o libcount.a
	gcc -Wall main.o libcount.a -o count

main.o: main.c
	gcc -c -v -Wall main.c -o main.o

libcount.a: readchar_R.o count_M.o
	ar -r libcount.a readchar_R.o libcount.a

readchar_R.o: readchar_R.c
	gcc -c -Wall readchar_R.c -o readchar_R.o

count_M.o: count_M.c
	gcc -c -Wall count_M.c -o count_M.o

test: test.c readchar_R.o count_M.o
	gcc -Wall test.c readchar_R.o count_M.o -o test

clean:
	rm -f *.o
	rm -f test
	rm -f count
	rm -f *.a