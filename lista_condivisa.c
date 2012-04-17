/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       lista_condivisa.c	                                       ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include "lista_condivisa.h"
#include "lista.h"
#include "semafori.h"

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int semid, id_mem;

int s_lista_ini(int *id){
	semid = crea_semaforo_lista();
	set_semaforo(S_READ, 1);
	set_semaforo(S_WRITE, 1);
	*id = shmget(key, sizeof(lista_statica), IPC_CREAT | 0600);
	if(*id == -1)
		return (listas) -1;
	listast = (listas) shmat(*id, NULL, 0);
	listast->n_elem = 0;
	return listast;
}

int s_lista_rimuovi(int *id){
	int err = shmctl(*id, IPC_RMID, 0);
	*id = 0;
	return err;
}

int s_lista_next(){
	
}
