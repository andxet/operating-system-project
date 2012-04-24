/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       lista_operatori.h                                           ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#ifndef helpdesk_lista_operatori_h
#define helpdesk_lista_operatori_h
#include "costanti.h"
#include "semafori.h"

int successivo, key, semid;

typedef struct lista_op * lista_operatori;
struct lista_op {
	int lista[MAX_N_OP]; //lista dei PID degli operatori
	int inPausa; //-1 nessun operatore in pausa, oppure PID operatore in pausa
};

extern lista_operatori operatori;
extern semaforo lista_sem;

int lista_operatori_ini();//Da utilizzare nel server, inizializza la memoria condivisa
int lista_operatori_aggancia();//Da utilizzare negli operatori, si aggancia alla coda del server
int lista_operatori_rimuovi();//Distrugge una memoria condivisa

int lista_operatori_inPausa();//Ottengo il PID dell'operatore in pausa
int lista_operatori_precedente();//Ottengo il PID dell'operatore precedente

int lista_operatori_next(int * next);//Ottengo il pid del prossimo operatore a cui assegnare una richiesta

int sgancia(); //Per scollegarsi da una memoria


#endif
