/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       miorandom.h                                                 ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include <time.h>

#ifndef helpdesk_util_h
#define helpdesk_util_h

#define miorandom(x) rand() % x

int gen_rand(int n);
void stampaLog(char * messaggio);

#endif
