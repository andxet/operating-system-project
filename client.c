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
#include "stato_helpdesk.h"
#include "operazioni_client.h"

int genera = 1, falliti = 0, numero_figli = 0;

void interrompi(int s);
void seppellisci(int s);

int main ()
{
	pid_t padre;
	
	srand((unsigned) time(NULL));
	
	signal(SIGINT, interrompi);
	signal(SIGCHLD, seppellisci);
	
	while(genera){
		padre = fork();
		if (!padre){ //Codice del figlio (quindi i vari client)
			exit(avviaClient());
		}
		else{
			/* Codice Padre */
			numero_figli++;
			sleep(gen_rand(1000)/1000);
		}
	}
	
	while(numero_figli > 0){
		sleep(1000);
	}
}

void interrompi(int s){
	stampaLog("Ricevuto SIGINT, si consiglia di uscire da questo programma terminando il processo helpdesk.");
}

void seppellisci(int s){
	int stato_figlio;
	
	wait(&stato_figlio);
	
	numero_figli--;
	
	if(WEXITSTATUS(stato_figlio) == -1)
		falliti ++;
	else
		falliti = 0;
	
	if (falliti > MAX_FALLIMENTI_HELPDESK){
		stampaLog("Falliti troppi tentativi di contattare l'helpdesk, esco.");
		genera = 0;
	}
}