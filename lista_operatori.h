//
//  lista_operatori.h
//  helpdesk
//
//  Created by Andrea Peretti on 13/04/12.
//  Copyright (c) 2012 Università degli studi di Torino. All rights reserved.
//

#ifndef helpdesk_lista_operatori_h
#define helpdesk_lista_operatori_h
#include "costanti.h"
#include "semafori.h"

int successivo, key, semid;



#define KEY_LISTA 998

typedef struct lista_op * lista_operatori;
struct lista_op {
	int lista[MAX_N_OP]; //lista dei PID degli operatori
	int inPausa; //-1 nessun operatore in pausa, oppure PID operatore in pausa
};

extern lista_operatori operatori;
extern semaforo lista_sem;

int lista_operatori_ini();
int lista_operatori_aggancia();
int lista_operatori_rimuovi();

int lista_operatori_inPausa();
int lista_operatori_precedente();

int lista_operatori_next(int * next);

int sgancia();


#endif
