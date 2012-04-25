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
	int memid = shmget(KEY_STATO_OP, sizeof(struct stato_hd), IPC_CREAT | 0600);
	if(memid == -1)
		return -1; //Errore nella creazione della coda
	stato_hd = (stato_helpdesk) shmat(memid, NULL, 0);
	if(stato_hd == -1)
		return -1;
	stato_hd->inPausa = -1;
	stato_hd->aperto = APERTO;
	return 0;
}

int stato_aggancia(){
	int memid = shmget(KEY_STATO_OP, sizeof(struct stato_hd), 0);
	if(memid == -1)
		return -1; //Coda inesistente od errore nel collegamento
	stato_hd = (stato_helpdesk) shmat(memid, NULL, 0);
}

int stato_rimuovi(){
	return shmctl(stato_hd, IPC_RMID, 0);
}

int stato_inPausa(){
	if((int)stato_hd <= -1)
		return -1;
	return stato_hd->inPausa;
}