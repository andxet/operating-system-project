/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       miacoda_cli.h                                               ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:   Header delle classi della coda cliente                      ##
##                                                                             ##
###############################################################################*/

#include "coda.h"

//Funzioni da utlilizzare nel client che deve chiedere aiuto all' helpdesk

//Variabili che devono essere dichiarate nel programma che utilizza queste funzioni
extern int coda;//id della coda ricevuto dopo l'inizializzazione
extern int op;//PID dell'operatore che gestirà la richiesta

int c_coda_ini(); //Inizializza la coda
int c_coda_aggancia(int id_coda); //Si aggancia alla coda di un operatore
int c_coda_telefona(); //Richiede al server di essere messo in coda per usufruire dell'helpdesk
int c_coda_invia_rich(int da_spedire); //Invia la domanda da porre all'operatore
int c_coda_attendi_op();//Attende la risposta dall'operatore in modo da sapere il suo PID
int c_coda_ricevi(int * ricevuto); //Riceve i messaggi destinati al client in questione
