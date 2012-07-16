# Progetto di Sistemi Operativi aa. 2011 2012
# makefile
# Fiori Peretti Polto

all: 
	make server client
	
#### Helpdesk

server: server.o operatore.o coda.o miacoda_op.o stato_helpdesk.o semafori.o util.o
	gcc -o helpdesk server.o operatore.o coda.o miacoda_op.o stato_helpdesk.o semafori.o util.o

server.o: server.c costanti.h makefile
	gcc -c server.c -g

operatore.o: operatore.c operatore.h costanti.h makefile
	gcc -c operatore.c -g
	
coda.o: coda.c coda.h costanti.h makefile
	gcc -c coda.c -g

miacoda_op.o: miacoda_op.c miacoda_op.h coda.o costanti.h makefile
	gcc -c miacoda_op.c -g
		
stato_helpdesk.o: stato_helpdesk.c stato_helpdesk.h costanti.h makefile
	gcc -c stato_helpdesk.c -g
	
util.o: util.c util.h costanti.h makefile
	gcc -c util.c -g
	
semafori.o: semafori.c semafori.h costanti.h makefile
	gcc -c semafori.c -g

##### Client

client: client.o  coda.o miacoda_cli.o stato_helpdesk.o semafori.o util.o operazioni_client.o
	gcc -o client client.o coda.o miacoda_cli.o stato_helpdesk.o semafori.o util.o operazioni_client.o

miacoda_cli.o: miacoda_cli.c miacoda_cli.h coda.o costanti.h makefile
	gcc -c miacoda_cli.c -g

operazioni_client.o: operazioni_client.c operazioni_client.h costanti.h makefile
	gcc -c operazioni_client.c -g

#### Altre funzioni

clean:
	rm ./*.o helpdesk client
