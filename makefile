main : img_read.o main.c
	gcc main.c img_read.o -o main
img_read.o:img_read.c
	gcc -c img_read.c -o img_read.o
