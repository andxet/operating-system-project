/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       semafori.c                                                  ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "client.h"

stato_helpdesk stato_hd;

int main ()
{
	int i;
	pid_t padre;	

	//while (1)
	//{
		//padre = fork();

		//if ( !padre ) //Codice del figlio (quindi i vari client)
		//{
			printf("Creato un nuovo client");
			
			//semaforo lista_sem;
		
			
			int result = stato_aggancia();
			if ( result == -1)
			 	printf("qualche errore qui");
			
			printf("stato helpdest %d \n", stato_hd->aperto);
			
		//}

			
	//}




}
