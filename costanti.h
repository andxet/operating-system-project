/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       costanti.h	                                               ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:   Costanti utilizzate all'interno del progetto                ##
##                                                                             ##
###############################################################################*/


#define MAX_N_OP  10 // Numero massimo di operatori che vengono creati dall'helpdesk
#define DIM_CODA_OP 10 // Dimensione della coda di ogni operatore
#define STATO_HELPDESK 0 //Indica se l'helpdesk è aperto (true) o chiuso (false)
#define DURATA_GIORNO 120 //Tempo (secondi) in cui l'helpdesk è attivo
#define DURATA_NOTTE 60 // Tempo (secondi) in cui l'helpdesk è disattivato

//Costranti per gli operatori
#define OP_PROB_PAUSA 4 //1/x = probabilità che l'operatore decida di andare in pausa dopo aver servito un cliente
#define OP_SEC_PAUSA 5 //Secondi di pausa

#define KEY_LISTA 998 //Chiave della memoria condivisa lista_operatori

/////////////////////// provenienti da coda.h ////////////////////////
//Viene definita la chiave della coda:
//999 per il server di spmistamento
#define ID_CODA 999 //key della coda helpdesk
#define MAX_ATTESA 10 //Dimensione della coda di attesa

//Definizione dei destinatari (tipo del messaggio, da assegnare al campo long del messaggio)
#define M_SERVER 100 //Server
					 //Per i processi client si userà il loro pid.

//Tipi di richieste
//Richiesta di aiuto all'helpdesk
#define RICH_OP 1

//Risposta dell'helpdesk all'aiuto
#define HD_RISPONDI 21

//Tipo di aiuto richiesto all'helpdesk
#define RICH_1	11 //Devono essere tutte consecuti, oppure rischio di segmentation fault
#define RICH_2	12
#define RICH_3	13
#define RICH_4	14

//Risposta alla richiesta da parte dell'helpdesk
#define OP_SOLUZIONE 22

//Risposta da parte del dispatcher in caso l'helpdesk sia chiuso
#define HD_CLOSED 31
#define HD_OCCUPATO 32