count: main.o libcount.a
	gcc -Wall main.o libcount.a -o count

main.o: main.c
	gcc -c -Wall main.c -o main.o

libcount.a: readchar_R.o count_M.o
	ar -r libcount.a readchar_R.o count.o

readchar_R.o: readchar_R.c
	gcc -c -Wall readchar_R.c -o readchar_R.o

count_M.o: count_M.c
	gcc -c -Wall count_M.c -o count_M.o

test: test.c readchar_R.o
	gcc test.c readchar_R.o -o test