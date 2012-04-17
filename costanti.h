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

