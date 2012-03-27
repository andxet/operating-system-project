/*
 *  semafori.h
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY 900

#define NUM_SEMAFORI 8
#define S_LOG 0
#define S_REP 1
#define S_LIS 2
#define S_MES 3
#define S_COD 4
#define S_SERV 5
#define S_LISUP 6
#define S_LISPU 7

int s_wait(int semid, int semnum);
int s_signal(int semid, int semnum);
int s_wait0(int semid, int semnum);
int rimuovi_sem(int semid);
int crea_semaforo(int num_semafori);
int collega_semaforo(int semnum);
int set_semaforo(int semid, int sem, int val);