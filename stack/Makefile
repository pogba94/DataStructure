CC = gcc
CFLAGS = -W -Wall -g

Target = stack.exe
Object = stack.o
RM = rm -f

$(Target) : $(Object)
	$(CC) $(CFLAGS) -o $(Target) $(Object)

.PHONY : clean
clean:
	$(RM) $(Target) $(Object)
	