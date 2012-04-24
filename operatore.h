/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       operatore.h                                                 ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#ifndef helpdesk_operatore_h
#define helpdesk_operatore_h

#include "lista_operatori.h"

int op; //Numero dell'operatore, che identifica l'ordine in cui è stato creato questo operatore (indice del ciclo che crea gli operatori
int servi; //Settato a true, indica quando l'op deve continuare a servire
int collega_gia_servito; //Booleano che indica se il collega in pausa è già stato servito
int coda; //Coda dell'operatore
stato_helpdesk stato_hd;
semaforo lista_sem;

int avvia(int idOp);


#endif
