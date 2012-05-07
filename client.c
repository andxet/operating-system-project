/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           			 ##
## --------------------------------------------------------------------------- ##
##  File:	       semafori.c                                                  ##
##  Created by:	   Fiori, Peretti, Polto                                     ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "costanti.h"
#include "util.h"
#include "operazioni_client.h"

int genera = 1, falliti = 0, numero_figli = 0;

void interrompi(int s);
void seppellisci(int s);

int main ()
{
	pid_t padre;
	
	signal(SIGINT, interrompi);
	signal(SIGCHLD, seppellisci);
	
	while(genera){
		if(LIMITA_PROCESSI)
		{//Devo attivare il limitatore dei processi figli
			if(numero_figli <= MAX_CLIENTI_GENERATI)
			{
				numero_figli++;
				padre = fork();
			}
			else
				sleep(1);//Non posso più genearare client
		}
		else
		{//Non ci sono limiti sui figli
			padre = fork();
		}
		

		if (!padre){ //Codice del figlio (quindi i vari client)
			genera=0;
			exit(avviaClient());
		}
		else{
			/* Codice Padre */
			//printf("GESTORE CLIENT -> Ho generato %d su %d client disponibili\n",numero_figli,MAX_CLIENTI_GENERATI);fflush(stdout);
			sleep(0.500);
		}
		//stampaLog("-------------------------------");
	}
	
	//while(numero_figli > 0){
	//	sleep(1000);
	//}
}

void interrompi(int s){
	//stampaLog("Ricevuto SIGINT, si consiglia di uscire da questo programma terminando il processo helpdesk.");
	genera = 0;
	MAX_CLIENTI_GENERATI=0;
}

void seppellisci(int s){
	int stato_figlio;
	//printf("**Seppellisco figlio : %d.\n",s);fflush(stdout);fflush(stdout); //Come mai da solo 17???
	wait(&stato_figlio);
	
	numero_figli--;
	//printf("**Numero figli: %d\n", numero_figli);fflush(stdout);
	//printf("wexitstatus: %d\n", WEXITSTATUS(stato_figlio));
	
	if(WEXITSTATUS(stato_figlio) == 10 || WEXITSTATUS(stato_figlio) == 30)
		falliti ++;
	else
		falliti = 0;
	//printf("**Hanno fallito : %d\n", falliti);fflush(stdout);
	
	if (falliti > MAX_FALLIMENTI_HELPDESK){
		stampaLog(">>>>Falliti troppi tentativi di contattare l'helpdesk, esco.");
		genera = 0;
	}
}
