CC = gcc
CFLAGS = -W -Wall -g

Target = linkedList.exe
Object = linkedList.o
RM = rm -f

$(Target) : $(Object)
	$(CC) $(CFLAGS) -o $(Target) $(Object)

.PHONY : clean
clean:
	$(RM) $(Target) $(Object)
	