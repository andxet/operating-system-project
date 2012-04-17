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

int s_wait(int semnum){
	struct sembuf cmd;
	
	cmd.sem_num = semnum;
	cmd.sem_op = -1;
	cmd.sem_flg = 0;
	
	return semop(semid, &cmd, 1);
}

int s_signal(int semnum){
	struct sembuf cmd;
	
	cmd.sem_num = semnum;
	cmd.sem_op = 1;
	cmd.sem_flg = 0;
	
	return semop(semid, &cmd, 1);
}

int s_wait0(int semnum){
	struct sembuf cmd;
	
	cmd.sem_num = semnum;
	cmd.sem_op = 0;
	cmd.sem_flg = 0;
	
	return semop(semid, &cmd, 1);
}

int rimuovi_sem(){
	return semctl(semid, IPC_RMID, 0);
}

int crea_semaforo(int num_semafori){
	return semget(key, num_semafori, 0600 | IPC_CREAT);
}

int crea_semaforo_lista(){
	return crea_semaforo(NUM_SEMAFORI);
}

int collega_semaforo(int semnum){
	return semget(key, semnum, 0);
}

int set_semaforo(int sem, int val){
	return semctl(semid, sem, SETVAL, val);
}
