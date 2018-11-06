CC = gcc
CFLAGS = -W -Wall -g

Target = biTree.exe
Object = biTree.o
RM = rm -f

$(Target) : $(Object)
	$(CC) $(CFLAGS) -o $(Target) $(Object)

.PHONY : clean
clean:
	$(RM) $(Target) $(Object)
