/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       lista.c	                                                   ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void lista_ini(listas lista){
    lista = (listas) malloc(sizeof(lista_statica));
    lista->n_elem = 0;
    //lista->vett = (int *) malloc(sizeof(int) * MAX_LISTA);
	int i;
	for(i = 0; i < MAX_LISTA; i++)
        lista->vett[i] = 0;
	//return lista;
}

int lista_e_in(listas lista, int dato){
	printf("\nFunzione lista è in: %d e %d", lista->n_elem, dato); fflush(stdout);
    int i;
    for(i = 0; i < MAX_LISTA; i++)
        if (lista->vett[i] == dato)
            return 1;
    return 0;
}

int lista_aggiungi(listas lista, int dato){
    if(lista->n_elem >= MAX_LISTA)
        return -2; //La coda è piena.
    if(!lista_e_in(lista, dato)){
        lista->vett[lista->n_elem] = dato;
        lista->n_elem++;
        return 0;
    }
    return -1; //L'elemento è già esistente.
}

       
void lista_print(listas lista){
    int i;
    for(i=0; i < lista->n_elem; i++){
        printf("\n %d) %d", i, lista->vett[i]);
    }
}
