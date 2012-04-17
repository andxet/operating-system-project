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
#include "coda.h"

#include <unistd.h>
#include <stdio.h>

//Funzioni ottimizzate per il client
int c_coda_ini(){
	if(coda_esiste(M_SERVER) == -1)
		return -2; //La coda non esiste!
	coda = coda_aggancia(M_SERVER);
	if(coda == -1)
		return -1; //Errore nel collegarsi alla coda
	return 0;
}

int c_coda_aggancia(int id_coda){
	if(coda_esiste(id_coda) == -1)
		return -2; //La coda non esiste!
	coda = coda_aggancia(id_coda);
	if(coda == -1)
		return -1; //Errore nel collegarsi alla coda
	return 0;
}

int c_coda_telefona(){//Invia al server 
	coda = c_coda_ini();
	coda_messaggio mess = coda_messaggio_componi(M_SERVER, getpid(), RICH_OP);
	return coda_spedisci(coda, mess);
}

int c_coda_invia_rich(int da_spedire){
	if(op == 0)
		return -1;//L'operatore a cui inviare la richiesta non è stato definito.
	coda_messaggio mess = coda_messaggio_componi(op, getpid(), da_spedire);
	return coda_spedisci(coda, mess);
}

int c_coda_attendi_op(){
	coda_messaggio mess;
	int err = coda_ricevi(coda, getpid(), &mess);
	if(mess.dato == HD_CLOSED)
		return -2;//L'helpdesk è chiuso
	if(mess.dato != OP_CIAO)
		return -3;//Messaggio inatteso
	op = mess.dato;
	return err;
}

int c_coda_ricevi(int * ricevuto){
	coda_messaggio mess;
	int err = coda_ricevi(coda, getpid(), &mess);
	*ricevuto = mess.dato;
	return err;
}
