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
#include <signal.h>


#include "operatore.h"
#include "miacoda_op.h"
#include "costanti.h"
#include "util.h"
#include "lista_operatori.h"

int tempistiche[4] = {0.100, 0.050, 0.500, 0.150}; //Secondi di attesa
int op; //Numero dell'operatore, che identifica l'ordine in cui è stato creato questo operatore (indice del ciclo che crea gli operatori
int key;
int servi; //Settato a true, indica quando l'op deve continuare a servire
int collega_gia_servito; //Booleano che indica se il collega in pausa è già stato servito
int coda; //Coda dell'operatore
stato_helpdesk stato_hd;
semaforo sem_coda;
semaforo sem_stato;

int opPrecedente();
void risolvi_problema(int problema);
int pausa();
int next_client();
void licenzia(int s);


int avvia(int idOp){  //avvia l'operatore
	signal(SIGINT, licenzia);
	op = idOp;
	key = KEY_START + op;
	srand((unsigned) time(NULL));//Inizializzo il motore per la creazione di numeri casuali
	int err = op_coda_ini(); //Crea la coda
	if(err < 0){
		stampaLog("Errore nella creazione della coda");
		exit(-1);
	}
	//log(sprintf("Operatore %d con chiave %d avviato", op, KEY_START+op));
	//Salva in memoria condivisa l'id dell'operatore, TODO:Controllo su quello che ritorna
	printf("In esecuzione operatore %d con chiave %d\n", op, KEY_START+op);
	sem_stato = collega_semaforo(SEM_HD);
	sem_coda = crea_semaforo(key);
	
	if(stato_aggancia() == -1){
		stampaLog("Errore nel collegarsi alla coda");
		exit(-1);
	}
	if((stato_hd) == -1){
		stampaLog("Stato helpdesk è a -1!");
		exit(-1);
	}
	if(sem_stato == -1){
		stampaLog("Il semaforo di stato helpdesk è a -1!");
		exit(-1);
	}
	if(sem_coda == -1){
		stampaLog("Il semaforo della coda è a -1!");
		exit(-1);
	}
	
	printf("Lo stato dell HD e': %d\n", stato_hd->aperto); fflush(stdout);
	
	set_semaforo(sem_coda, DIM_CODA_OP);
	
	collega_gia_servito = 0;
	while(stato_hd->aperto != FALLIMENTO){
		coda_messaggio ricevuto;
		if(next_client(&ricevuto) == -1)   //Serve per prelevare il messaggio del cliente
			continue;
		int client = ricevuto.sender;
		int problema = ricevuto.dato - RICH_1;
		risolvi_problema(problema);				//Risolve il problema e dorme
		op_coda_invia_soluzione(client);		//Risponde ho risolto il problemaKEYnd(OP_PROB_PAUSA) == 1)		//Vede se mett in pausa
		{}//pausa(); TODO: DA SCOMMENTARE UNA VOLTA IMPLEMENTATI I SEMAFORI
		s_signal(sem_coda);
	}

	printf("%d: Ok ultimo respiro e poi muoio *_*\n",getpid());	
	exit(0);
}

int next_client(coda_messaggio * messCliente){
	int codat;
	//TODO: ottenere accesso lettura alla lista
	if(stato_hd->inPausa != -1 && stato_hd->inPausa == opPrecedente() && !collega_gia_servito){//Se l'operatore precedente è in pausa e non ho già servito un suo cliente, estraggo un cliente dalla sua lista
		codat = coda_aggancia(opPrecedente());
		collega_gia_servito = 1;
	}
	else{
		 codat = coda;
		 collega_gia_servito = 0;
	}
	
	return op_coda_ricevi_collega(messCliente, codat);  //Serve per prendere il mess da codat e lo salva in &cliente		
}

void risolvi_problema(int problema){
	//TODO: Controllare che problema sia compreso nel range di tempistiche
	sleep(tempistiche[problema]);
}

int opPrecedente(){
	return KEY_START + ((op - 1 + MAX_N_OP)%MAX_N_OP);
}

void licenzia(int s){
	printf("%d: Elimino la coda : %d\n",getpid(),coda);
	coda_rimuovi(coda);
	printf("%d: Elimino il semaforo : %d\n",getpid(),sem_coda);
	rimuovi_sem(sem_coda);
	printf("%d: Ho eliminato tutto posso morire in pace +_+\n",getpid());	
}

int pausa(){
	//TODO: implementare utilizzo dei semafori
	if(stato_inPausa() != -1)
		return 0;//Qualcuno è già in pausa
	stato_hd->inPausa = KEY_START + op;
	//Rilascio semaforo
	sleep(OP_SEC_PAUSA);
	//Ottengo accesso alla lista
	stato_hd->inPausa = -1;
	return 1;//Riprendo a lavorare
}
