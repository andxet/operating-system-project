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

//TODO: Decidere se mantenere extern o lasciarlo all'interno di questo programma
extern int key;
extern int semid;

typedef int semaforo;

#define NUM_SEMAFORI 2
#define S_READ	0
#define S_WRITE 1

//Creazione e rimozione
int crea_semaforo(int num_semafori);
int crea_semaforo_lista();
int collega_semaforo(int semnum);

//Operazioni su semafori
int s_wait(int semnum);
int s_signal(int semnum);
int s_wait0(int semnum);
int rimuovi_sem();
int set_semaforo(int sem, int val);
