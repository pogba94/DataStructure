CC = gcc
CFLAGS = -W -Wall -g

Target = huffmanEncode.exe
Object = huffmanEncode.o
RM = rm -f

$(Target) : $(Object)
	$(CC) $(CFLAGS) -o $(Target) $(Object)

.PHONY : clean
clean:
	$(RM) $(Target) $(Object)