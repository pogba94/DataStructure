CC = gcc
CFLAGS = -W -Wall -g

Target = rbTree.exe
Object = rbTree.o
RM = rm -f

$(Target) : $(Object)
	$(CC) $(CFLAGS) -o $(Target) $(Object)

.PHONY : clean
clean:
	$(RM) $(Target) $(Object)
