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

int MAX_CLIENTI_GENERATI = 100;	//Questa variabile serve solo per il debugg


int genera = 1, falliti = 0, numero_figli = 0;

void interrompi(int s);
void seppellisci(int s);

int main ()
{
	pid_t padre;
	
	signal(SIGINT, interrompi);
	signal(SIGCHLD, seppellisci);
	
	while(genera){
		if(numero_figli <= MAX_CLIENTI_GENERATI)
		{
			//stampaLog("-_-^->Forkatooooo");
			numero_figli++;
			padre = fork();
			
		}
		else
			sleep(1);
			//printf("GESTORE CLIENT -> Non posso piu' generare figli  %d su %d generati\n",numero_figli,MAX_CLIENTI_GENERATI);fflush(stdout);

		if (!padre){ //Codice del figlio (quindi i vari client)
			//stampaLog("Sono nel figlio");
			genera=0;
			exit(avviaClient());
		}
		else{
			/* Codice Padre */
			//stampaLog("Sono nel padre");
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
