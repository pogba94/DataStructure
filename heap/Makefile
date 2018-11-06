CC = gcc
CFLAGS = -W -Wall -g

Target = heap.exe
Object = heap.o
RM = rm -f

$(Target) : $(Object)
	$(CC) $(CFLAGS) -o $(Target) $(Object)

.PHONY : clean
clean:
	$(RM) $(Target) $(Object)
