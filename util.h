/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       miorandom.h                                                 ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##  DA ELIMINARE PER ME (VITTO)
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include <time.h>

#ifndef helpdesk_util_h
#define helpdesk_util_h

#define random(x) rand() % x
#define randomize srand((unsigned)time(NULL))

int gen_rand(int n);
void log(char * messaggio);

#endif