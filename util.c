/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       miorandom.c	                                               ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##   DA ELIMINARE PER ME (VITTO)
###############################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <sys/signal.h>

int gen_rand(int n)
/* returns random number in range of 0 to 99 */
{
	return random(n);
}

void log(char * messaggio){
	printf("\n%d: %s", getpid(), messaggio);
}