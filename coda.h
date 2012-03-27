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
#include "repo.h"

//Viene definita la chiave della coda
#define ID_CODA 811
#define MAX_ATTESA 10

//Definizione dei destinatari (tipo del messaggio, da assegnare al campo long del messaggio)
#define M_SERVER 100 //Server
//Per i processi client si userà il loro pid.

//Tipi di richieste
#define RICH_UPLOAD 20 //Il client invia prima il suo ID di client di upload, quando il server gli risponde, può inviare il pacchetto o nel caso che non venga autenticato richiedere l'accreditamento per l'upload.
#define RICH_ACCREDITA 21 //Il client invia una richiesta di accreditamento per l'upload, il server risponde con una conferma in caso affermativo.
#define RICH_DOWNLOAD 22 //Il client invia una stringa in cui è presente il nome di un programma.
#define RICH_AGGIORNA 23 //Il client riceverà prima il numero di programmi presenti del repository, poi ogni programma ad uno ad uno.
#define RICH_AGGIORNAMENTI 24
#define RICH_PUSH 25
#define SEGN_AGG 30
//#define RICH_NOOP 100 //Utilizzata nel caso in cui viene ricevuto un segnale durante l'attesa di un messaggio, che interrompe l'attesa.

//Tipi di risposte
#define RISP_DOWNLOAD 32
#define RISP_AGGIORNA 33
#define RISP_AGGIORNAMENTI 34
#define RISP_PUSH 35
#define RISP_ACCREDITA 36
#define RISP_UP 37


#ifndef CODA_PACCO
typedef struct pacco coda_dato;
struct pacco{
	int tipo; //Contiene la richiesta o la risposta.
	union{//La union contiene il dato associato alla richiesta.
	repo_pacchetto programma;
	int dato;
	char nome[LUNGH_NOME_PACC];
	//float versione;
	};
};
#define CODA_PACCO
#endif

#ifndef CODA_MESSAGGIO
typedef struct coda_messaggio coda_messaggio;
struct coda_messaggio {
	long dest; //Verrà usata la dichiarazione dei destinatari qui sopra, oppure il PID del processo ricevente.
	int sender; //PID del processo chiamante
	coda_dato dato; //Tipo di messaggio (il messaggio vero e proprio) //Decidere se utilizare una union
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
coda_messaggio coda_messaggio_componi(long destinatario, int pids, coda_dato datot);