/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       miacoda_op.h                                                ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:   Header delle classi della coda di operatori                 ##
##                                                                             ##
###############################################################################*/


#include "coda.h"

extern int coda;
//extern int client;


int op_coda_ini();//Funzione per collegarsi alla coda
//int op_coda_presentati();//Funzione per far sapere al client che verrà servito da questo operatore
int op_coda_invia_soluzione();//Invia la soluzione una volta elaborata
int op_coda_ricevi(coda_messaggio * ricevuto);//Riceve la domanda dal client
int op_coda_ricevi_collega(coda_messaggio * ricevuto, int coda_c);
