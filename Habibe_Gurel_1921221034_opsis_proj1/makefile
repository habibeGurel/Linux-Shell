CC=gcc
CFLAGS=-c	-Wall
all:makeSonuc
makeSonuc:	myShell.o	execx.o	writef.o
	$(CC)	myShell.o	-o	makeSonuc

execx.o:	execx.c
	$(CC)	execx.c -o execx
writef.o:	writef.c
	$(CC)	writef.c -o writef
clean:
	del	*.o	
run:
	makeSonuc1.exe