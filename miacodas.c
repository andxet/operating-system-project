/*
 *  miacodac.c
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#include <unistd.h>

#include "miacodas.h"
#include "coda.h"

//Funzioni ottimizzate per il server

int s_coda_ini(int * coda){
	if(coda_esiste() != -1)
		return -2; //La coda esiste già!
	*coda = coda_crea();
	if(*coda == -1)
		return -1; //Errore nella creazione della coda
	return 0;
}

int s_coda_invia(int coda, coda_dato da_inviare, long dest){
	coda_messaggio mess = coda_messaggio_componi(dest, M_SERVER, da_inviare);
	return coda_spedisci(coda, mess);
}

int s_coda_ricevi(int coda, coda_dato * ricevuto, int * sender){
	coda_messaggio mess;
	int err = coda_ricevi(coda, M_SERVER, &mess);
	*sender = (int) mess.sender;
	*ricevuto = mess.dato;
	return err;
}

int s_coda_ricevi_mio(int coda, coda_dato * ricevuto, long * sender){
	coda_messaggio mess;
	int err = coda_ricevi(coda, getpid(), &mess);
	*sender = (int) mess.sender;
	*ricevuto = mess.dato;
	return err;
}


int s_coda_elimina(int coda){
	return coda_rimuovi(coda);
}

int s_coda_elimina_esistente(){
	int coda;
	if(!coda_esiste())
		return -1;//La coda non esiste.
	coda = coda_aggancia();
	return coda_rimuovi(coda);
}