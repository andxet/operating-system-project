/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       miorandom.c	                                               ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int gen_rand(int n){
	return miorandom(n);
}

void stampaLog(char * messaggio){
	if(DEBUG)
	{
		printf("%d : %s\n", getpid(), messaggio); fflush(stdout);
	}
}
