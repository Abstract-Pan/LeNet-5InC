main : img_read.o main.c objects.o
	gcc main.c img_read.o objects.o -o main -g
img_read.o:img_read.c
	gcc -c img_read.c -o img_read.o
object.o : object.c
	gcc -c objects.c -o object.o -g
