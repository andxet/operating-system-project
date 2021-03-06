/*############################################################
 ##         -= Progetto di Sistemi Operativi =-             ##
 ## --------------------------------------------------------##
 ##  File:	       miacoda_op.c                             ##
 ##  Created by:	   Fiori, Peretti, Polto                ##
 ##                                                         ##
 ###########################################################*/

#include "miacoda_op.h"
#include "coda.h"
#include <unistd.h>
#include "costanti.h"
#include "util.h"

//Funzioni ottimizzate per l'operatore

int op_coda_ini(){
	coda = coda_crea(KEY_START+op);
	if(coda == -1){
		return -1; //Errore nel collegarsi alla coda
	}
	return 0;
}

int op_coda_invia_soluzione(int client){
	coda_messaggio mess = coda_messaggio_componi(client, M_SERVER, OP_SOLUZIONE);
	return coda_spedisci(coda, mess);
}

int op_coda_ricevi(coda_messaggio * ricevuto){
	return op_coda_ricevi_collega(ricevuto, coda);
}

int op_coda_ricevi_collega(coda_messaggio * ricevuto, int coda_c){
	int err = coda_ricevi(coda_c, M_SERVER, ricevuto);
	return err;
}


int op_coda_invia_soluzione_CHIUSO(int client){
	coda_messaggio mess = coda_messaggio_componi(client, M_SERVER, OP_SOLUZIONE_CHIUSO);
	return coda_spedisci(coda, mess);
}
