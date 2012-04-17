/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       operatore.c                                                 ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "operatore.h"
#include "miacoda_op.h"
#include "costanti.h"
#include "miorandom.h"
#include "lista_operatori.h"



coda_messaggio next_client();
void risolvi_problema(int problema);
int pausa();

int avvia(int idOp){
	srand((unsigned) time(NULL));
	if(coda_esiste(getpid()))
		return -1;//Coda già esistente
	coda = op_coda_ini();
	lista_operatori_aggancia();
	//TODO: collega al semaforo della memoria condivisa
	op = idOp;
	servi = 1;
	collega_gia_servito = 0;
	while(servi){
		coda_messaggio ricevuto = next_client();
		int client = ricevuto.sender;
		int problema = ricevuto.dato;
		risolvi_problema(problema);
		op_coda_invia_soluzione(client);
		if(gen_rand(OP_PROB_PAUSA) == 1)
			pausa();
	}
	coda_rimuovi(coda);
	exit(0);
}

coda_messaggio next_client(){
	int codat;
	//TODO: ottenere accesso lettura alla lista
	if(operatori->inPausa == operatori->lista[(op-1+MAX_N_OP)%MAX_N_OP] && !collega_gia_servito){//Se l'operatore precedente è in pausa e non ho già servito un suo cliente, estraggo un cliente dalla sua lista
		codat = coda_aggancia(operatori->lista[(op-1+MAX_N_OP)%MAX_N_OP]);
		collega_gia_servito = 1;
	}
	else{
		 codat = coda;
		 collega_gia_servito = 0;
	}
		 
	coda_messaggio cliente;
	int err = op_coda_ricevi_collega(&cliente, codat);
	if (err < 0){
		fprintf(stderr, "Errore nel prelevare dalla coda (Operatore %d PID %d", op, getpid());
		exit(-1);
	}
	return cliente;		
}

void risolvi_problema(int problema){
	sleep(tempistiche[problema]);
}

int pausa(){
	//TODO: implementare utilizzo dei semafori
	if(lista_operatori_inPausa() != -1)
		return 0;//Qualcuno è già in pausa
	operatori->inPausa = getpid();
	//Rilascio semaforo
	sleep(OP_SEC_PAUSA);
	//Ottengo accesso alla lista
	operatori->inPausa = -1;
	return 1;//Riprendo a lavorare
}
