/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           			 ##
## --------------------------------------------------------------------------- ##
##  File:	       miorandom.c	                                              ##
##  Created by:	   Fiori, Peretti, Polto                                     ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "semafori.h"

int gen_rand(int n){
	return (rand() % n);
}

void avvia_motore_rand(){
	srand((unsigned) time(NULL) + getpid());//Inizializzo il motore per la creazione di numeri casuali
}

void stampaLog(char * messaggio){
	if(DEBUG)
	{
		semaforo sem_print = collega_semaforo(SEM_PRINT);		//Creato semaforo per l'output
		s_wait(sem_print);
		printf("%d : %s\n", getpid(), messaggio); fflush(stdout);
		s_signal(sem_print);
	}
}
