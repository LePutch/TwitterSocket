OBJ1 = server.o clientServer.o

EXEC = ${OBJ1} server
all: ${EXEC}

clientServer.o : clientServer.c clientServer.h
	gcc  -g -c  clientServer.c

server.o : server.c server.h clientServer.h
	gcc  -g -c  server.c

server : ${OBJ1} 
	gcc ${OBJ1} -o server 

clean :
	rm ${EXEC}
