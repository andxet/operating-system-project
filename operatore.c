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
#include "stato_helpdesk.h"

int op; //Numero dell'operatore, che identifica l'ordine in cui è stato creato questo operatore (indice del ciclo che crea gli operatori
int key;
//float tempistiche[N_MAX_RICH] = {0.100, 0.050, 0.500, 0.150}; //Secondi di attesa
float tempistiche[N_MAX_RICH] = {1, 2, 3, 4}; //Secondi di attesa

int collega_gia_servito; //Booleano che indica se il collega in pausa è già stato servito

int coda; //Coda dell'operatore
semaforo sem_coda;

stato_helpdesk stato_hd;

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
	printf("%d : Operatore: avviato key :%d\n",getpid(),key);fflush(stdout);
	srand((unsigned) time(NULL));//Inizializzo il motore per la creazione di numeri casuali
	
	//Aggangio alle risorse IPC dell'helpdesk
	if(stato_aggancia() == -1){//Controllo per collegarsi alla memoria condivisa dell'helpdesk
		stampaLog("Errore nel collegarsi alla coda");
		exit(-1);
	}
	if((long)stato_hd == -1){//Controllo 
		stampaLog("Stato helpdesk è a -1!");
		exit(-1);
	}
	sem_stato = collega_semaforo(SEM_HD);
	if(sem_stato == -1){
		stampaLog("Il semaforo di stato helpdesk è a -1!");
		exit(-1);
	}
	if(sem_coda == -1){
		stampaLog("Il semaforo della coda è a -1!");
		exit(-1);
	}
	
	
	//Creazione risorse IPC dell'operatore
	sem_coda = crea_semaforo(key);
	if(op_coda_ini() < 0 || sem_coda < 0){
		stampaLog("Errore nell'allocazione delle risorse IPC");
		exit(-1);
	}
	set_semaforo(sem_coda, DIM_CODA_OP);
	
	//stampaLog("Pronto a servire");
	printf("%d : Operatore: pronto a servire\n",getpid());fflush(stdout);
	
	collega_gia_servito = 0;
	while(stato_hd->aperto != FALLIMENTO){
		coda_messaggio ricevuto;
		if(next_client(&ricevuto) == -1)   //Serve per prelevare il messaggio del cliente
		{
			printf("%d : Operatore: CONTINUEEEEEEEEEEEEEEEE\n",getpid());fflush(stdout);
			continue;
		}
		stampaLog("************************************************");
		printf("%d : Operatore: Inizio sequenza operazioni\n",getpid());fflush(stdout);
		int client = ricevuto.sender;
		int problema = ricevuto.dato;
		printf("%d : Operatore: Servo client: %d, richiesta :%d\n",getpid(),client,problema);fflush(stdout);
		risolvi_problema(problema);				//Risolve il problema e dorme
		printf("%d : Operatore: Invio la soluzione al client: %d\n",getpid(),client);fflush(stdout);
		op_coda_invia_soluzione(client);		//Risponde ho risolto il problemaKEYnd(OP_PROB_PAUSA) == 1)		//Vede se mett in pausa
		printf("%d : Operatore: Client liquidato incremento il semaforo\n",getpid());fflush(stdout);
		s_signal(sem_coda);
/* Per ora nessun operatore va in pausa */
		//pausa();
		//printf("\n");fflush(stdout);
		stampaLog("************************************************");
	}

	stampaLog("Helpdesk in chiusura, uscita.");
	exit(0);
}

int next_client(coda_messaggio * messCliente){
	int codat;
	s_wait(sem_stato);//Serve per accedere alla memoria dell HD e controllare che OP è in pausa
	if(stato_hd->inPausa != -1 && stato_hd->inPausa == opPrecedente() && !collega_gia_servito){//Se l'operatore precedente è in pausa e non ho già servito un suo cliente, estraggo un cliente dalla sua lista
		codat = coda_aggancia(opPrecedente());
		stampaLog("Servo un cliente del mio collega in pausa.");
		collega_gia_servito = 1;
	}
	else{
		 codat = coda;
		 collega_gia_servito = 0;
		stampaLog("Servo un mio cliente.");
	}
	s_signal(sem_stato);
	return op_coda_ricevi_collega(messCliente, codat);  //Serve per prendere il mess da codat e lo salva in &cliente		
}

void risolvi_problema(int problema){
	if(problema < 0 || problema > N_MAX_RICH)
		return;
	printf("%d : Operatore: Eseguo la richiesta, dormo :%f\n",getpid(),tempistiche[problema]);fflush(stdout);
	sleep(tempistiche[problema]);
}

int opPrecedente(){
	return KEY_START + ((op - 1 + MAX_N_OP)%MAX_N_OP);
}

void licenzia(int s){
	//printf("%d: Elimino la coda : %d\n",getpid(),coda);
	coda_rimuovi(coda);
	//printf("%d: Elimino il semaforo : %d\n",getpid(),sem_coda);
	rimuovi_sem(sem_coda);
	//printf("%d: Ho eliminato tutto posso morire in pace +_+\n",getpid());	
}

int pausa(){
	s_wait(sem_stato);
	int inPausa = stato_inPausa();
	if(inPausa != -1){
		stampaLog("Qualcuno è in pausa, pazienza...");
		s_signal(sem_stato);
		return 0;//Qualcuno è già in pausa
	}
	stampaLog("Vado in pausa!");
	stato_hd->inPausa = KEY_START + op;
	s_signal(sem_stato);
	
	sleep(OP_SEC_PAUSA);
	
	s_wait(sem_stato);
	stato_hd->inPausa = -1;
	stampaLog("Esco dalla pausa...");
	s_signal(sem_stato);
	return 1;//Riprendo a lavorare
}
