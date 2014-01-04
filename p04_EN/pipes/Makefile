p4: cap_trans.o demux.o io_mux.o main.o str_hdl.o
	gcc -Wall cap_trans.o demux.o io_mux.o main.o str_hdl.o -o p4

main.o: main.c main.h
	gcc -Wall -c main.c -o main.o

io_mux.o: io_mux.c io_mux.h
	gcc -Wall -c io_mux.c -o io_mux.o

demux.o: demux.c demux.h
	gcc -Wall -c demux.c -o demux.o

cap_trans.o: cap_trans.c cap_trans.h
	gcc -Wall -c cap_trans.c -o cap_trans.o

str_hdl.o: str_hdl.c str_hdl.h
	gcc -Wall -c str_hdl.c -o str_hdl.o

clean:
	rm -f p4
	rm -f *.o