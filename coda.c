/*
 *  coda.c
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

//Funzione che restituisce l'indice della coda, creandola.
#include "coda.h"

int coda_crea(){
	return msgget(ID_CODA, 0666 | IPC_CREAT);
}

int coda_esiste(){
	return msgget(ID_CODA, 0666 | IPC_EXCL);
}

//Funzione che restituisce l'indice della coda, agganciandosi ad essa
int coda_aggancia(){
	return msgget(ID_CODA, 0);
}

//Funzione che spedisce il messaggio nella coda
int coda_spedisci(int coda, coda_messaggio mess){
	return msgsnd(coda, &mess, sizeof(coda_messaggio) - sizeof(long), 0);
}

int coda_ricevi(int coda, int tipo, coda_messaggio *ricevuto){
	//alarm(MAX_ATTESA);
	return (int) msgrcv(coda, ricevuto,  sizeof(coda_messaggio) - sizeof(long), tipo, 0);
}

int coda_rimuovi(int coda){
	return msgctl(coda, IPC_RMID, 0);
}

coda_messaggio coda_messaggio_componi(long destinatario, int pids, coda_dato datot){
	coda_messaggio nuovo_mess;
	nuovo_mess.dest = destinatario;
	nuovo_mess.sender = pids;
	nuovo_mess.dato = datot;
	return nuovo_mess;
}
