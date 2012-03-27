/*
 *  miacoda.c
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#include "miacodac.h"
#include "coda.h"
#include <unistd.h>

//Funzioni ottimizzate per il client

int c_coda_ini(int * coda){
	if(coda_esiste() == -1)
		return -2; //La coda non esiste!
	*coda = coda_aggancia();
	if(*coda == -1)
		return -1; //Errore nel collegarsi alla coda
	return 0;
}

int c_coda_invia(int coda, coda_dato da_spedire){
	coda_messaggio mess = coda_messaggio_componi(M_SERVER, getpid(), da_spedire);
	return coda_spedisci(coda, mess);
}

int c_coda_invia_serv(int coda, coda_dato da_spedire, int serv_pid){
	coda_messaggio mess = coda_messaggio_componi(serv_pid, getpid(), da_spedire);
	return coda_spedisci(coda, mess);
}

int c_coda_ricevi(int coda, coda_dato * ricevuto){
	coda_messaggio mess;
	int err = coda_ricevi(coda, getpid(), &mess);
	*ricevuto = mess.dato;
	return err;
}