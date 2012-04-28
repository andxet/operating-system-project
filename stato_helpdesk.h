/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       stato_helpdesk.h                                           ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#ifndef helpdesk_lista_operatori_h
#define helpdesk_lista_operatori_h
#include "costanti.h"
#include "semafori.h"



//int successivo, key, semid;

typedef struct stato_hd * stato_helpdesk;
struct stato_hd {
	int inPausa; //-1 nessun operatore in pausa, oppure PID operatore in pausa
	int aperto;//0 chiuso, 1 fallimento (esci dal programma), 2 aperto
};

extern stato_helpdesk stato_hd;

int stato_ini();//Da utilizzare nel server, inizializza la memoria condivisa
int stato_aggancia();//Da utilizzare negli operatori, si aggancia alla coda del server
int stato_rimuovi();//Distrugge una memoria condivisa

int stato_inPausa();//Ottengo il PID dell'operatore in pausa

int sgancia(); //Per scollegarsi da una memoria


#endif
