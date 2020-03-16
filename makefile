MyProg: error.o analize_input_line.o label.o
	gcc -g -ansi -I -Wall -pedantic error.o analize_input_line.o label.o -o MyProg

error.o: error.c 
	gcc -c -ansi -I -Wall -pedantic error.c -o error.o

analize_input_line.o: analize_input_line.c
	gcc -c -ansi -I -Wall -pedantic analize_input_line.c -o analize_input_line.o

label.o: label.c 
	gcc -c -ansi -I -Wall -pedantic label.c -o label.o
