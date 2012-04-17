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



#define KEY_LISTA 998

typedef struct lista_op * lista_operatori;
struct lista_op {
	int lista[MAX_N_OP]; //lista dei PID degli operatori
	int inPausa; //-1 nessun operatore in pausa, oppure PID operatore in pausa
};

extern lista_operatori operatori;
extern semaforo lista_sem;

int lista_operatori_ini();
int lista_operatori_aggancia();
int lista_operatori_rimuovi();

int lista_operatori_inPausa();
int lista_operatori_precedente();

int lista_operatori_next(int * next);

int sgancia();


#endif
