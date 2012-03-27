//
//  mialista_s.h
//  repository
//
//  Created by Andrea Peretti on 11/04/11.
//  Copyright 2011 Università degli studi di Torino. All rights reserved.
//

#include "mialista.h"

/*#ifndef LISTA_SHARED

typedef struct lista_condivisa lista_condivisa;
typedef lista_condivisa * lista_sh;

struct lista_condivisa{
	listas lista;
	int shmid_lista;
};

#define LISTA_SHARED
#endif*/

listas s_listas_ini();
int s_listas_rimuovi(int *id);