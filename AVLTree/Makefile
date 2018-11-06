CC = gcc
CFLAGS = -W -Wall -g

Target = AVLTree.exe
Object = AVLTree.o
RM = rm -f

$(Target) : $(Object)
	$(CC) $(CFLAGS) -o $(Target) $(Object)

.PHONY : clean
clean:
	$(RM) $(Target) $(Object)