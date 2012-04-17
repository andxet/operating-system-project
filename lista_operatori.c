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

int lista_operatori_ini(){
	lista_sem = crea_semaforo(2);
	set_semaforo(S_READ, 1);
	set_semaforo(S_WRITE, 1);
	int memid = shmget(KEY_LISTA, sizeof(struct lista_op), IPC_CREAT | 0600);
	if(memid == -1)
		return -1; //Errore nella creazione della coda
	operatori = (lista_operatori) shmat(memid, NULL, 0);
	operatori->inPausa = -1;
	successivo = 0;
	return 0;
}

int lista_operatori_aggancia(){
	int memid = shmget(KEY_LISTA, sizeof(struct lista_op), 0);
	if(memid == -1)
		return -1; //Coda inesistente od errore nel collegamento
	operatori = (lista_operatori) shmat(memid, NULL, 0);
	return 0;
}

int lista_operatori_rimuovi(){
	return shmdt(operatori);
}

int lista_operatori_inPausa(){
	if((int)operatori <= -1)
		return -1;
	return operatori->inPausa;
}

int lista_operatori_precedente(){
	extern int op;
	if(!op)
		return -1;
	return operatori->lista[(op+MAX_N_OP-1)%MAX_N_OP];
}

int lista_operatori_next(int * next){
	return operatori->lista[((successivo++)+MAX_N_OP)%MAX_N_OP];
	
}
