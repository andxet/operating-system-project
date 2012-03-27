//
//  mialista_s.c
//  repository
//
//  Created by Andrea Peretti on 11/04/11.
//  Copyright 2011 Università degli studi di Torino. All rights reserved.
//

#include "mialistas.h"
#include "mialista.h"

#include "miorepos.h"
#include <stdio.h>

listas s_listas_ini(int *id){
	listas listast;
	*id = shmget(S_KEY, sizeof(lista_statica), IPC_CREAT | 0600);
	if(*id == -1)
		return (listas) -1;
	listast = (listas) shmat(*id, NULL, 0);
	listast->n_elem = 0;
	return listast;
}

int s_listas_rimuovi(int *id){
	int err = shmctl(*id, IPC_RMID, 0);
	*id = 0;
	return err;
}