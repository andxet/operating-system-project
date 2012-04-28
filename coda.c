/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       coda.c	                                                   ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

//Funzione che restituisce l'indice della coda, creandola.
#include "coda.h"

int coda_crea(int id){
	return msgget(id, 0666 | IPC_CREAT);
}

int coda_esiste(int id){
	if(msgget(id, 0666 | IPC_EXCL) == -1)
		return 1;
	else
		return 0;
}

//Funzione che restituisce l'indice della coda, agganciandosi ad essa
int coda_aggancia(int id){
	return msgget(id, 0);
}

//Funzione che spedisce il messaggio nella coda
int coda_spedisci(int coda, coda_messaggio mess){
	return msgsnd(coda, &mess, sizeof(coda_messaggio) - sizeof(long), 0);
}

int coda_ricevi(int coda, int tipo, coda_messaggio *ricevuto){
	return (int) msgrcv(coda, ricevuto,  sizeof(coda_messaggio) - sizeof(long), tipo, 0);
}

int coda_rimuovi(int coda){
	return msgctl(coda, IPC_RMID, 0);
}

coda_messaggio coda_messaggio_componi(long destinatario, int pids, int datot){
	coda_messaggio nuovo_mess;
	nuovo_mess.dest = destinatario;
	nuovo_mess.sender = pids;
	nuovo_mess.dato = datot;
	return nuovo_mess;
}
