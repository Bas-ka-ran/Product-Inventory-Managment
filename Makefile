
all: inventory

inventory: pro_invent_man_main.o pro_invent_man_functions.o
	gcc -o inventory pro_invent_man_main.o pro_invent_man_functions.o

pro_invent_man_main.o: pro_invent_man_main.c pro_invent_man_header.h
	gcc -c pro_invent_man_main.c

pro_invent_man_functions.o: pro_invent_man_functions.c pro_invent_man_header.h
	gcc -c pro_invent_man_functions.c

clean:
	rm -f *.o inventory
