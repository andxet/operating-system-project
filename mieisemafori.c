/*
 *  semafori.c
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#include "mieisemafori.h"

int s_wait(int semid, int semnum){
	struct sembuf cmd;
	
	cmd.sem_num = semnum;
	cmd.sem_op = -1;
	cmd.sem_flg = 0;
	
	return semop(semid, &cmd, 1);
}

int s_signal(int semid, int semnum){
	struct sembuf cmd;
	
	cmd.sem_num = semnum;
	cmd.sem_op = 1;
	cmd.sem_flg = 0;
	
	return semop(semid, &cmd, 1);
}

int s_wait0(int semid, int semnum){
	struct sembuf cmd;
	
	cmd.sem_num = semnum;
	cmd.sem_op = 0;
	cmd.sem_flg = 0;
	
	return semop(semid, &cmd, 1);
}

int rimuovi_sem(int semid){
	return semctl(semid, IPC_RMID, 0);
}

int crea_semaforo(int num_semafori){
	return semget(KEY, num_semafori, 0600 | IPC_CREAT);
}

int collega_semaforo(int semnum){
	return semget(KEY, semnum, 0);
}

int set_semaforo(int semid, int sem, int val){
	return semctl(semid, sem, SETVAL, val);
}