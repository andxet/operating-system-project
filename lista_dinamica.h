/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       lista_dinamica.h                                            ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

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
