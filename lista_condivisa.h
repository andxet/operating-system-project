//
//  mialista_s.h
//  repository
//
//  Created by Andrea Peretti on 11/04/11.
//  Copyright 2011 Università degli studi di Torino. All rights reserved.
//

#include "lista.h"

/*#ifndef LISTA_SHARED

typedef struct lista_condivisa lista_condivisa;
typedef lista_condivisa * lista_sh;

struct lista_condivisa{
	listas lista;
	int shmid_lista;
};

#define LISTA_SHARED
#endif*/

extern listas listast;
extern int key;

int s_lista_ini(int *id);
int s_lista_rimuovi(int *id);
int s_lista_aggancia();
int s_lista_scollega();

int s_lista_next();
int s_lista_aggiungi();