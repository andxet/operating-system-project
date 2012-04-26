/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       costanti.h	                                               ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:   Costanti utilizzate all'interno del progetto                ##
##                                                                             ##
###############################################################################*/

#ifndef costanti

#define MAX_N_OP  10 // Numero massimo di operatori che vengono creati dall'helpdesk
#define DIM_CODA_OP 10 // Dimensione della coda di ogni operatore
					   //#define STATO_HELPDESK 0 //Indica se l'helpdesk è aperto (true) o chiuso (false)
#define DURATA_GIORNO 12 //Tempo (secondi) in cui l'helpdesk è attivo
#define DURATA_NOTTE 6 // Tempo (secondi) in cui l'helpdesk è disattivato

#define MAX_FALLIMENTI_HELPDESK 10

//Costranti per gli operatori
#define OP_PROB_PAUSA 4 //1/x = probabilità che l'operatore decida di andare in pausa dopo aver servito un cliente
#define OP_SEC_PAUSA 5 //Secondi di pausa

#define KEY_STATO_OP 998 //Chiave della memoria condivisa stato_helpdesk

/////////////////////// provenienti da coda.h ////////////////////////
//Viene definita la chiave della coda:
//999 per il server di spmistamento
#define SEM_HD 888
#define MAX_ATTESA 10 //Dimensione della coda di attesa

//Definizione dei destinatari (tipo del messaggio, da assegnare al campo long del messaggio)
#define M_SERVER 100 //Server
					 //Per i processi client si userà il loro pid.


//Tipo di aiuto richiesto all'helpdesk
#define N_MAX_RICH 4

//Risposta alla richiesta da parte dell'helpdesk
#define OP_SOLUZIONE 22

//Vettore delle chiavi delle code degli operatori
//int code[DIM_CODA_OP] = {1000, 1001, 1002, 1003
#define KEY_START 1000

#define costanti
#endif