/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       semafori.c                                                  ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include "semafori.h"

int s_wait(int semid){
	struct sembuf cmd;
	
	cmd.sem_num = 0;
	cmd.sem_op = -1;
	cmd.sem_flg = 0;
	
	return semop(semid, &cmd, 1);
}

int s_signal(int semid){
	struct sembuf cmd;
	
	cmd.sem_num = 0;
	cmd.sem_op = 1;
	cmd.sem_flg = 0;
	
	return semop(semid, &cmd, 1);
}

int s_wait0(int semid){
	struct sembuf cmd;
	
	cmd.sem_num = 1;
	cmd.sem_op = 0;
	cmd.sem_flg = 0;
	
	return semop(semid, &cmd, 1);
}

int rimuovi_sem(int semid){
	return semctl(semid, IPC_RMID, 0);
}

int crea_semaforo(int key){
	return semget(key, 1, 0600 | IPC_CREAT);
}

int collega_semaforo(int key){
	return semget(key, 0, 0);
}

int set_semaforo(int semid, int val){
	return semctl(semid, 0, SETVAL, val);
}
