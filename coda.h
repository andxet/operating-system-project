/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       coda.h	                                                   ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Header del file coda                                       ##
##                                                                             ##
###############################################################################*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
//#include "repo.h"

#ifndef CODA_MESSAGGIO
typedef struct coda_messaggio coda_messaggio;
struct coda_messaggio {
	long dest;	//Verrà usata la dichiarazione dei destinatari qui sopra, oppure il PID del processo ricevente.
	int sender; //PID del processo chiamante
	int dato;	//Dato da comunicare
};
#define CODA_MESSAGGIO
#endif

//Funzione che restituisce l'indice della coda, creandola.
int coda_crea(int id);
int coda_esiste(int id);
//Funzione che restituisce l'indice della coda, agganciandosi ad essa
int coda_aggancia(int id);
//Funzione che spedisce il messaggio nella coda
int coda_spedisci(int coda, coda_messaggio mess);
int coda_ricevi(int coda, int tipo, coda_messaggio *ricevuto);
int coda_rimuovi(int coda);
coda_messaggio coda_messaggio_componi(long destinatario, int pids, int datot);
