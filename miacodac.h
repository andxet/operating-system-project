/*
 *  miacoda.h
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */
#include "coda.h"

int c_coda_ini(int * coda);
int c_coda_invia(int coda, coda_dato da_spedire);
int c_coda_ricevi(int coda, coda_dato * ricevuto);
int c_coda_invia_serv(int coda, coda_dato da_spedire, int serv_pid);