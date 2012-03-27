/*
 *  miologs.c
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#include "miologs.h"
#include "mieisemafori.h"

int shmid_buf = 0;

miolog s_buf_ini(char * nome_log){
	miolog buf;
	shmid_buf = shmget(L_KEY, sizeof(log_buf), IPC_CREAT | 0666);
	if(shmid_buf == -1)
		return (miolog) -1;
	buf = (miolog) shmat(shmid_buf, NULL, 0);
	
	if (strlen(nome_log) > L_NOME_LOG) { //Evito un errore di segmentazione controllando la lunghezza della stringa da copiare.
		return (miolog) -2;
	}
	strcpy(buf->nomelog, nome_log); //Memorizzo il nome del file di log passato come parametro.
	buf->num_mess = 0;//Inizializzo il buffer del log.
	
	return buf;
}

int s_buf_rimuovi(){
	return shmctl(shmid_buf, IPC_RMID, 0);
}