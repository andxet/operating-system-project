/*
 *  miacodac.h
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */
#include "coda.h"

int s_coda_ini(int * coda);
int s_coda_invia(int coda, coda_dato da_inviare, long dest);
int s_coda_ricevi_mio(int coda, coda_dato * ricevuto, long * sender);
int s_coda_ricevi(int coda, coda_dato * rivevuto, int * sender);
int s_coda_elimina(int coda);
int s_coda_elimina_esistente();