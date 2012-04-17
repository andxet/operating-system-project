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

int tempistiche[4] = {0.100, 0.050, 0.500, 0.150};
int op, servi, collega_gia_servito, coda;
lista_operatori operatori;
semaforo lista_sem;

int avvia(int idOp);


#endif
