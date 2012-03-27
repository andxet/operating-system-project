/*
 *  log.c
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#include "log.h"

#include <unistd.h>
#include <string.h>

//Inizializzazione del buffer
miolog buf_init(char * nome_file){
	if (strlen(nome_file) > L_NOME_LOG) { //Evito un erore di segmentazione controllando la lunghezza della stringa da copiare.
		return (miolog) -2;
	}
	miolog log = (miolog) malloc(sizeof(log_buf));
	strcpy(log->nomelog, nome_file); //Memorizzo il nome del file di log passato come parametro.
	log->num_mess = 0;//Inizializzo il buffer del log.
	return log;
}

//Scrivo il buffer nel file
int buf_flush(miolog buf){
	if (buf->num_mess == 0) {
		return 0;
	}
	if (strcmp(buf->nomelog, "") == 1) {//Se il nome del file è nullo, assegno un nome
		strcpy(buf->nomelog, "log.log");
	}
	FILE *file_log = fopen(buf->nomelog, "a");
	if (file_log == NULL)
		return -1; //Errore apertura file.
	int i;
	for (i=0; i < buf->num_mess; i++)
		fprintf(file_log, "\n%d %s: %s", buf->messaggi[i].proc_pid, buf->messaggi[i].tipop, buf->messaggi[i].messaggio);
	buf->num_mess = 0;
	fprintf(file_log, "\n%d %s: %s", getpid(), MIOBUF_DAEMON, FLUSH_BUF);
	fclose(file_log);
	return 0; //Buffer salvato ed azzerato.
}

//Sposta mes2 in mes1
void buf_sposta_mess(struct log_messaggio *mes1, struct log_messaggio *mes2){
	mes1->proc_pid = mes2->proc_pid;
	strcpy(mes1->tipop, mes2->tipop);
	strcpy(mes1->messaggio, mes2->messaggio);
}

//Inserisce un messaggio nel buffer in memoria.
int buf_inserisci(miolog buf, log_messaggio mess){
	buf_sposta_mess(&buf->messaggi[buf->num_mess], &mess);
	buf->num_mess++;
	if(buf->num_mess >= MAX_MESS_LOG)
		buf_flush(buf);
	return 0;
}

struct log_messaggio buf_messaggio_componi(char tipop[], char messaggio[]){
	log_messaggio nuovo_mes;
	nuovo_mes.proc_pid = getpid();
	strcpy(nuovo_mes.tipop, tipop);
	strcpy(nuovo_mes.messaggio, messaggio);
	return nuovo_mes;
}