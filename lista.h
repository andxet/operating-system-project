//
//  mialista.h
//  repository
//
//  Created by Andrea Peretti on 10/04/11.
//  Copyright 2011 Università degli studi di Torino. All rights reserved.
//

//TODO: decidere se definire la dimensione della coda qui oppure in operatore.h
#define MAX_LISTA 30
//extern int MAX_LISTA;

#ifndef LISTAS

typedef struct lista_statica lista_statica;
typedef lista_statica * listas;

struct lista_statica{
	int n_elem;
	int vett[MAX_LISTA];
};

#define LISTAS
#endif

void lista_ini(listas lista);
int lista_e_in(listas lista, int dato);
int lista_aggiungi(listas lista, int dato);    
void lista_print(listas lista);