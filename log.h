/*
 *  log.h
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define MAX_MESS_LOG 10 //Dimensione del buffer
#define TIPOP_DIM 20 //Dimensione della stringa del tipo operazione. Settato com il numero di caratteri del tipo più lungo.
#define MESS_DIM 65 //Dimensione della stringa messaggio. Settato com il numero di caratteri del messaggio più lungo.

//Defininizione dei messaggi
#define FLUSH_BUF "Il buffer è stato salvato."

//Definizione tipo processi
#define MIOBUF_DAEMON "Gestore buffer"



#ifndef LOG_MESSAGGIO
typedef struct log_messaggio log_messaggio;
struct log_messaggio{
	int proc_pid; //PID del processo che scrive
	char tipop[TIPOP_DIM]; //Tipo processo che scrive
	char messaggio[MESS_DIM]; //Testo del messaggio da scrivere
};
#define LOG_MESSAGGIO
#endif

#ifndef LOG_BUF
#define L_NOME_LOG 30
typedef struct log_buf log_buf;
typedef log_buf *miolog;
struct log_buf{
	log_messaggio messaggi[MAX_MESS_LOG];//Vettore con tutti i messaggi
	char nomelog[L_NOME_LOG];
	int num_mess;//Numero messaggi attualmente presenti
};
#define LOG_BUF
#endif

//Inizializzazione del buffer
miolog buf_init(char * nome_file);
//Scrivo il buffer nel file
int buf_flush(miolog buf);
//Sposta mes2 in mes1
void buf_sposta_mess(struct log_messaggio *mes1, struct log_messaggio *mes2);
//Inserisce un messaggio nel buffer in memoria.
int buf_inserisci(miolog buf, log_messaggio mess);
struct log_messaggio buf_messaggio_componi(char tipop[], char messaggio[]);

