/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       lista_operatori.c	                                       ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include <stdio.h>
#include "lista_operatori.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "costanti.h"

int stato_ini(){
	lista_sem = crea_semaforo(2);
	set_semaforo(S_READ, 1);
	set_semaforo(S_WRITE, 1);
	int memid = shmget(KEY_LISTA, sizeof(struct stato_hd), IPC_CREAT | 0600);
	if(memid == -1)
		return -1; //Errore nella creazione della coda
	stato_hd = (stato_helpdesk) shmat(memid, NULL, 0);
	stato_hd->inPausa = -1;
	stato_hd->aperto = 1;
	int i;
	
	successivo = 0;
	return 0;
}

int stato_aggancia(){
	int memid = shmget(KEY_LISTA, sizeof(struct stato_hd), 0);
	if(memid == -1)
		return -1; //Coda inesistente od errore nel collegamento
	stato_hd = (stato_helpdesk) shmat(memid, NULL, 0);
	return 0;
}

int stato_rimuovi(){
	return shmdt(stato_hd);
}

int stato_inPausa(){
	if((int)stato_hd <= -1)
		return -1;
	return stato_hd->inPausa;
}