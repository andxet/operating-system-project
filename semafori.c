/*############################################################
 ##         -= Progetto di Sistemi Operativi =-             ##
 ## --------------------------------------------------------##
 ##  File:	       semafori.c                               ##
 ##  Created by:	   Fiori, Peretti, Polto                ##
 ##                                                         ##
 ###########################################################*/

#include "semafori.h"
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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

/* Funzione per il debug */
int get_val_sem(int semid){
	return semctl(semid,0,GETVAL,0);
}
