//
//  operatore.h
//  helpdesk
//
//  Created by Andrea Peretti on 12/04/12.
//  Copyright (c) 2012 Università degli studi di Torino. All rights reserved.
//

#ifndef helpdesk_operatore_h
#define helpdesk_operatore_h

#include "lista_operatori.h"

int tempistiche[4] = {0.100, 0.050, 0.500, 0.150};
int op, servi, collega_gia_servito, coda;
lista_operatori operatori;
semaforo lista_sem;

int avvia(int idOp);


#endif
