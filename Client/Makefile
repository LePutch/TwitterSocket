all: client

client : client.o
	gcc -o client client.o

client.o : client.c 
	gcc -Wall -c client.c 

clean :
	rm -f client *.o *~ 
