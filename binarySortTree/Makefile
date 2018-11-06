CC = gcc
CFLAGS = -W -Wall -g

Target = binarySortTree.exe
Object = binarySortTree.o
RM = rm -f

$(Target) : $(Object)
	$(CC) $(CFLAGS) -o $(Target) $(Object)

.PHONY : clean
clean:
	$(RM) $(Target) $(Object)
