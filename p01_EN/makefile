all: mem_experiment

mem_experiment: mem_experiment.o dynamic_mem.o
	gcc mem_experiment.o dynamic_mem.o -o mem_experiment -g -Wall

mem_experiment.o: mem_experiment.c dynamic_mem.h
	gcc -c mem_experiment.c -o mem_experiment.o -g -Wall

dynamic_mem.o: dynamic_mem.c dynamic_mem.h
	gcc -c dynamic_mem.c -o dynamic_mem.o -g -Wall

clean:
	rm -f *.o
