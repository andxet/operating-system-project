/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       miorandom.h                                                 ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/


#ifndef helpdesk_util_h

#include <time.h>

#define miorandom(x) rand() % x

int gen_rand(int n);
void stampaLog(char * messaggio);

#define helpdesk_util_h
#endif
