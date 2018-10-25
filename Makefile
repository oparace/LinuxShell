GCC = gcc

OBJS = main.o execute.o inputread.o argorg.o

default: myshell

myshell: $(OBJS)
	$(GCC) -o myshell $(OBJS)

inputread.o: inputread.c 
	$(GCC) -c inputread.c -o inputread.o

argorg.o: argorg.c 
	$(GCC) -c argorg.c -o argorg.o

execute.o: execute.c
	$(GCC) -c execute.c -o execute.o

main.o: main.c
	$(GCC) -c main.c -o main.o

clean: 
	rm $(OBJS)