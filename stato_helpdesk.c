/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       stato_helpdesk.c	                                       ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include <stdio.h>
#include "stato_helpdesk.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "costanti.h"

int memid;

int stato_ini(){
	memid = shmget(KEY_STATO_OP, sizeof(struct stato_hd), IPC_CREAT | 0600);
	if(memid == -1)
		return -1; //Errore nella creazione della coda
	stato_hd = (stato_helpdesk) shmat(memid, NULL, 0);
	if(stato_hd == -1)
		return -1;
	stato_hd->inPausa = -1;
	stato_hd->aperto = APERTO;
	//printf("stato_helpdesk.c -> Allocata la mem condivisa %d \n",stato_hd);
	printf("stato_helpdesk.c -> memid %d \n",memid);
	
	return 0;
}

int stato_aggancia(){
	int memid = shmget(KEY_STATO_OP, sizeof(struct stato_hd), 0);
	if(memid == -1)
		return -1; //Coda inesistente od errore nel collegamento
	stato_hd = (stato_helpdesk) shmat(memid, NULL, 0);
	return 0;
}

int stato_rimuovi(){
	printf("stato_helpdesk.c -> Devo eliminare la mem condivisa %d \n",memid);
	return shmctl(memid, IPC_RMID, 0);//c'era uno zero prima
}

int stato_inPausa(){
	if((int)stato_hd <= -1)
		return -1;
	return stato_hd->inPausa;
}
