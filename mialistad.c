/*
 *  mialista.c
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#include "mialistad.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

listad ls_aggiungi(listad mialista, int dato, int * errore){
	nodo * punt = mialista;
	while (punt != 0 && punt->dato != dato) {
		punt = punt->next;
	}
	if (punt != 0) {
		*errore = -1; //Già presente
		return mialista;
	}
	punt = mialista;
	mialista = (listad) malloc(sizeof(nodo));
	mialista->dato = dato;
	mialista->next = punt;
	errore = 0;
	return mialista;
}

int ls_e_in(listad mialista, int dato){
	nodo * punt = mialista;
	while (punt != 0 && punt->dato != dato) {
		punt = punt->next;
	}
	if (punt != 0) {
		return 1;
	}
	else {
		return 0;
	}
}


void ls_print(listad mialista){
	listad punt = mialista;
	int i = 1;
	while (punt != 0){
		printf("\n %d) %d", i++, punt->dato);
		punt = punt->next;
	}
}