/*
 *  miacodac.c
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#include <unistd.h>

#include "miacoda_serv.h"
#include "coda.h"

//Funzioni ottimizzate per il server

int s_coda_ini(){
	if(coda_esiste(ID_CODA) != -1)
		return -2; //La coda esiste già!
	coda = coda_crea(ID_CODA);
	if(coda == -1)
		return -1; //Errore nella creazione della coda
	return 0;
}

int s_coda_rispondi(int * sender){
	coda_messaggio mess;
	int err = coda_ricevi(coda, M_SERVER, &mess);
	*sender = mess.sender;
	return err;
}

int s_invia_chiuso(int dest){
	coda_messaggio mess = coda_messaggio_componi(dest, M_SERVER, HD_CLOSED);
	return coda_spedisci(coda, mess);
}

int s_invia_occupato(int dest){
	coda_messaggio mess = coda_messaggio_componi(dest, M_SERVER, HD_OCCUPATO);
	return coda_spedisci(coda, mess);
}

int s_coda_elimina(){
	return coda_rimuovi(coda);
}

int s_coda_elimina_esistente(){
	int coda;
	if(!coda_esiste(ID_CODA))
		return -2;//La coda non esiste.
	coda = coda_aggancia(ID_CODA);
	return coda_rimuovi(coda);
}