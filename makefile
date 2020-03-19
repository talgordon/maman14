MyProg: analize_code_word.o error.o analize_input_line.o label.o translate.o modules.o build.o assembler.o
	gcc -g -ansi -I -Wall -pedantic analize_code_word.o error.o analize_input_line.o label.o translate.o modules.o build.o assembler.o -o MyProg
error.o: error.c 
	gcc -c -ansi -I -Wall -pedantic error.c -o error.o

label.o: label.c 
	gcc -c -ansi -I -Wall -pedantic label.c -o label.o


analize_input_line.o: analize_input_line.c
	gcc -c -ansi -I -Wall -pedantic analize_input_line.c -o analize_input_line.o

analize_code_word.o: analize_code_word.c 
	gcc -c -ansi -I -Wall -pedantic analize_code_word.c -o analize_code_word.o

translate.o: translate.c 
	gcc -c -ansi -I -Wall -pedantic translate.c -o translate.o

modules.o: modules.c 
	gcc -c -ansi -I -Wall -pedantic modules.c -o modules.o

build.o: build.c 
	gcc -c -ansi -I -Wall -pedantic build.c -o build.o

assembler.o: assembler.c 
	gcc -c -ansi -I -Wall -pedantic assembler.c -o assembler.o

