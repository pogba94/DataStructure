CC = gcc
CFLAGS = -W -Wall -g

Target = queue.exe
Object = queue.o
RM = rm -f

$(Target) : $(Object)
	$(CC) $(CFLAGS) -o $(Target) $(Object)

.PHONY : clean
clean:
	$(RM) $(Target) $(Object)