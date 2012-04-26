# Progetto di Sistemi Operativi aa. 2011 2012
# repository
# Fiori Peretti Polto

all: 
	make server client
	
#### Helpdesk

server: server.o operatore.o coda.o miacoda_op.o stato_helpdesk.o semafori.o util.o
	gcc -o helpdesk server.o operatore.o coda.o miacoda_op.o stato_helpdesk.o semafori.o util.o

server.o: server.c
	gcc -c server.c

operatore.o: operatore.c operatore.h
	gcc -c operatore.c -g
	
coda.o: coda.c coda.h
	gcc -c coda.c -g

miacoda_op.o: miacoda_op.c miacoda_op.h
	gcc -c miacoda_op.c -g
	
#miacoda_cli.o: miacoda_cli.c miacoda_cli.h
#	gcc -c miacoda_cli.c -g
	
stato_helpdesk.o: stato_helpdesk.c stato_helpdesk.h
	gcc -c stato_helpdesk.c -g
	
util.o: util.c util.h
	gcc -c util.c
	
semafori.o: semafori.c semafori.h
	gcc -c semafori.c

##### Client
##TODO: fare il make per il client

client: client.o  coda.o miacoda_cli.o stato_helpdesk.o semafori.o util.o
	gcc -o client client.o coda.o miacoda_cli.o stato_helpdesk.o semafori.o util.o


#### Altre funzioni

clean:
	rm ./*.o helpdesk client
