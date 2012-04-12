/*
 *  miacoda.h
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */
#include "coda.h"

extern int coda;
//extern int client;


int op_coda_ini();//Funzione per collegarsi alla coda
//int op_coda_presentati();//Funzione per far sapere al client che verrà servito da questo operatore
int op_coda_invia_soluzione();//Invia la soluzione una volta elaborata
int op_coda_ricevi(coda_messaggio * ricevuto);//Riceve la domanda dal client
int op_coda_ricevi_collega(coda_messaggio * ricevuto, int coda_c);