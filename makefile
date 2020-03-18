MyProg: error.o analize_input_line.o label.o translate.o analize_code_word.o
	gcc -g -ansi -I -Wall -pedantic error.o analize_input_line.o label.o -o MyProg

analize_code_word.o: analize_code_word.c 
	gcc -c -ansi -I -Wall -pedantic analize_code_word.c -o analize_code_word.o

error.o: error.c 
	gcc -c -ansi -I -Wall -pedantic error.c -o error.o

analize_input_line.o: analize_input_line.c
	gcc -c -ansi -I -Wall -pedantic analize_input_line.c -o analize_input_line.o

label.o: label.c 
	gcc -c -ansi -I -Wall -pedantic label.c -o label.o

translate.o: translate.c 
	gcc -c -ansi -I -Wall -pedantic translate.c -o translate.o

