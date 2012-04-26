/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       miacoda_cli.c	                                           ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:   Classi coda per quanto riguarda i clienti                   ##
##                                                                             ##
###############################################################################*/

#include "miacoda_cli.h"
#include "costanti.h"
#include "coda.h"

#include <unistd.h>
#include <stdio.h>

//Funzioni ottimizzate per il client

int c_coda_aggancia(){/* Id coda è la coda a cui vuole collegarsi il cliente OFFSET + numeroOP ( numeroOP --> Random (0, MAX_NUM_OP))*/

	if(coda_esiste(key) == -1)
		return -2; //La coda non esiste!
	coda = coda_aggancia(key);
	if(coda == -1)
		return -1; //Errore nel collegarsi alla coda
	return 0;
}


int c_coda_invia_rich(int da_spedire){
	if(coda == -1)
		return -1;//L'operatore a cui inviare la richiesta non è stato definito.
	coda_messaggio mess = coda_messaggio_componi(M_SERVER, getpid(), da_spedire);
	return coda_spedisci(coda, mess);
}

int c_coda_attendi_op(){
	coda_messaggio mess;
	int err = coda_ricevi(coda, getpid(), &mess);
	if(err == -1)
		return err;
	else if(mess.dato == OP_SOLUZIONE)
		return 0;//L'helpdesk ha risposto
	else
		return -1;
}