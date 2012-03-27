/*
 *  mialista.h
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#ifndef NODO

typedef struct nodo nodo;
typedef nodo * listad;

struct nodo{
	int dato;
	nodo * next;
};
 
#define NODO
#endif

int ls_e_in(listad mialista, int dato);
listad ls_aggiungi(listad mialista, int dato, int * errore);
void ls_print(listad mialista);