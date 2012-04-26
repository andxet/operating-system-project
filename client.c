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

#include "costanti.h"
#include "stato_helpdesk.h"
#include "operazioni_client.h"


stato_helpdesk stato_hd;

int main ()
{
	int i;
	pid_t padre;
	int result = stato_aggancia();
	if ( result == -1)
		printf("Errore nell'agganciarsi alla memoria condivisa\n");
	else
		printf("Collegato correttamente alla memoria %d\n",result);
		/*Per ora provo con un solo figlio */
		padre = fork();

		if ( !padre ) //Codice del figlio (quindi i vari client)
		{
			printf("Creato un nuovo client\n");
			//avviaFiglio();
			//exit(0);
			
		}
		else
		{
			/* Codice Padre */
			int k=0;
			for(k=0; k<500;k++)
			{
				printf("%d)stato helpdest %d \n",k, stato_hd->aperto);
				sleep(1);
			}
		}			
}
