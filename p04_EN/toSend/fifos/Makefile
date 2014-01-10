all: cap_trans.o demux.o io_mux.o str_hdl.o
	gcc -g -Wall cap_trans.o -o tx
	gcc -g -Wall io_mux.o str_hdl.o -o io_mux
	gcc -g -Wall demux.o str_hdl.o -o demux
	rm -f T0 T1 T2 T3 T4 T5 T6 T7 T8 T9
	mkfifo T0 T1 T2 T3 T4 T5 T6 T7 T8 T9

io_mux.o: io_mux.c io_mux.h
	gcc -g -Wall -c io_mux.c -o io_mux.o

demux.o: demux.c demux.h
	gcc -g -Wall -c demux.c -o demux.o

cap_trans.o: cap_trans.c cap_trans.h
	gcc -g -Wall -c cap_trans.c -o cap_trans.o

str_hdl.o: str_hdl.c str_hdl.h
	gcc -g -Wall -c str_hdl.c -o str_hdl.o

clean:
	rm -f *.o
	rm -f tx
	rm -f io_mux
	rm -f demux
	rm -f T0 T1 T2 T3 T4 T5 T6 T7 T8 T9

fifo:
	mkfifo T0 T1 T2 T3 T4 T5 T6 T7 T8 T9