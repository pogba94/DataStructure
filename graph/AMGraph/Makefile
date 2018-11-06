CC = gcc
CFLAGS = -W -Wall -g

Target = AMGraph.exe
Object = AMGraph.o stack.o queue.o
RM = rm -f

$(Target) : $(Object)
	$(CC) $(CFLAGS) -o $(Target) $(Object)

.PHONY : clean
clean:
	$(RM) $(Target) $(Object)
