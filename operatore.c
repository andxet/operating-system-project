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
#include "util.h"
#include "lista_operatori.h"

int tempistiche[4] = {0.100, 0.050, 0.500, 0.150}; //Secondi di attesa



coda_messaggio next_client();
void risolvi_problema(int problema);
int pausa();

int avvia(int idOp){  //avvia l'operatore
	srand((unsigned) time(NULL));
	int err = op_coda_ini(); //Crea la coda
	if(err < 0)
		log("Errore nella creazione della coda, err: %d");
	log("Tutto ok");
	lista_operatori_aggancia();  //Salva in memoria condivisa l'id dell'operatore, TODO:Controllo su quello che ritorna
	//TODO: collega al semaforo della memoria condivisa
	op = idOp;
	servi = 1;
	collega_gia_servito = 0;
	while(servi){
		coda_messaggio ricevuto = next_client();   //Serve per prelevare il messaggio del cliente
		int client = ricevuto.sender;
		int problema = ricevuto.dato - RICH_1;
		risolvi_problema(problema);				//Risolve il problema e dorme
		op_coda_invia_soluzione(client);		//Risponde ho risolto il problema
		if(gen_rand(OP_PROB_PAUSA) == 1)		//Vede se mett in pausa
		{}//pausa(); TODO: DA SCOMMENTARE UNA VOLTA IMPLEMENTATI I SEMAFORI
	}
	coda_rimuovi(coda);
	exit(0);
}

coda_messaggio next_client(){
	int codat;
	//TODO: ottenere accesso lettura alla lista
	if(operatori->inPausa != -1 && operatori->inPausa == operatori->lista[(op-1+MAX_N_OP)%MAX_N_OP] && !collega_gia_servito){//Se l'operatore precedente è in pausa e non ho già servito un suo cliente, estraggo un cliente dalla sua lista
		codat = coda_aggancia(operatori->lista[(op-1+MAX_N_OP)%MAX_N_OP]);
		collega_gia_servito = 1;
	}
	else{
		 codat = coda;
		 collega_gia_servito = 0;
	}
		 
	coda_messaggio messCliente;
	int err = op_coda_ricevi_collega(&messCliente, codat);  //Serve per prendere il mess da codat e lo salva in &cliente
	if (err < 0){
		fprintf(stderr, "Errore nel prelevare dalla coda (Operatore %d PID %d", op, getpid());
		exit(-1);
	}
	return messCliente;		
}

void risolvi_problema(int problema){
	//TODO: Controllare che problema sia compreso nel range di tempistiche
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
