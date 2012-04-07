/*
 *  coda.h
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
//#include "repo.h"

//Viene definita la chiave della coda:
//999 per il server di spmistamento
#define ID_CODA 999
#define MAX_ATTESA 10

//Definizione dei destinatari (tipo del messaggio, da assegnare al campo long del messaggio)
#define M_SERVER 100 //Server
//Per i processi client si userà il loro pid.

//Tipi di richieste
//Richiesta di aiuto all'helpdesk
#define RICH_OP 1

//Risposta dell'helpdesk all'aiuto
#define OP_CIAO 21

//Tipo di aiuto richiesto all'helpdesk
#define RICH_1	11
#define RICH_2	12
#define RICH_3	13
#define RICH_4	14

//Risposta alla richiesta da parte dell'helpdesk
#define OP_SOLUZIONE 22

//Risposta da parte del dispatcher in caso l'helpdesk sia chiuso
#define HD_CLOSED 31


/*
#ifndef CODA_PACCO
typedef struct pacco coda_dato;
struct pacco{
	int tipo; //Contiene la richiesta o la risposta.
	union{//La union contiene il dato associato alla richiesta.
	int dato;
		//char nome[LUNGH_NOME_PACC];
	};
};
#define CODA_PACCO
#endif
*/


#ifndef CODA_MESSAGGIO
typedef struct coda_messaggio coda_messaggio;
struct coda_messaggio {
	long dest;	//Verrà usata la dichiarazione dei destinatari qui sopra, oppure il PID del processo ricevente.
	int sender; //PID del processo chiamante
	int dato;	//Dato da comunicare
};
#define CODA_MESSAGGIO
#endif

//Funzione che restituisce l'indice della coda, creandola.
int coda_crea();
int coda_esiste();
//Funzione che restituisce l'indice della coda, agganciandosi ad essa
int coda_aggancia();
//Funzione che spedisce il messaggio nella coda
int coda_spedisci(int coda, coda_messaggio mess);
int coda_ricevi(int coda, int tipo, coda_messaggio *ricevuto);
int coda_rimuovi(int coda);
coda_messaggio coda_messaggio_componi(long destinatario, int pids, int datot);