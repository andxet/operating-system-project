/*
 *  miacoda.c
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#include "miacoda_op.h"
#include "coda.h"
#include <unistd.h>

//Funzioni ottimizzate per l'operatore

int op_coda_ini(){
	if(coda_esiste(getpid()) != -1)
		return -2; //La coda esiste già!
	coda = coda_crea(getpid());
	if(coda == -1)
		return -1; //Errore nel collegarsi alla coda
	return 0;
}

/*int op_coda_presentati(){
	if(client == 0)
		return -1;
	coda_messaggio mess = coda_messaggio_componi(client, getpid(), OP_CIAO);
	return coda_spedisci(coda, mess);
 }*/ //Non necessaria perchè ci pensa lo scheduler

int op_coda_invia_soluzione(int client){
	coda_messaggio mess = coda_messaggio_componi(client, getpid(), OP_SOLUZIONE);
	return coda_spedisci(coda, mess);
}

int op_coda_ricevi(coda_messaggio * ricevuto){
	return op_coda_ricevi_collega(ricevuto, coda);
}

int op_coda_ricevi_collega(coda_messaggio * ricevuto, int coda_c){
	int err = coda_ricevi(coda_c, getpid(), ricevuto);
	return err;
}