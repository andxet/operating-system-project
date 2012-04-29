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
float tempistiche[N_MAX_RICH] = {3, 3, 4, 5}; //Secondi di attesa

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
/* Cose kikko */
int statoHD = STATO_INIZIALE_HD;
int nMessInCoda = 0;
void cambiatoStatoHD(int signum);
/************/

int avvia(int idOp){  //avvia l'operatore
	signal(SIGUSR1,cambiatoStatoHD);
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
	int esitoSet = set_semaforo(sem_coda, DIM_CODA_OP);
	printf("%d : Semaforo settato esito : %d, valore :%d\n",getpid(),esitoSet,DIM_CODA_OP);
	int nClientInCoda = get_val_sem(sem_coda);
	printf("%d : Operatore: Ho settato il mio semaforo a :%d \n",getpid(),nClientInCoda);fflush(stdout);
	
	printf("%d : Operatore: pronto a servire\n",getpid());fflush(stdout);
	
	collega_gia_servito = 0;
	while(stato_hd->aperto != FALLIMENTO){
		coda_messaggio ricevuto;
		/* Differenzio i 3 casi :
				- 1° HD Aperto
				- 2° HD Chiuso, ma l'op ha ancora da servire alcuni clienti
				- 3° HD Chiso, Op ha risposto a tutte i clienti, deve rispondere negativamente a quelli che entrano
		*/
		stampaLog("************************************************");
		if(stato_hd->aperto == APERTO)
		{//1°Caso
			if(next_client(&ricevuto) == -1)   //Serve per prelevare il messaggio del cliente
			{
				printf("%d : Operatore1°c: CONTINUEEEEEEEEEEEEEEEE\n",getpid());fflush(stdout);
				continue;
			}
			
			//printf("%d : Operatore1°c: Inizio sequenza operazioni\n",getpid());fflush(stdout);
			int client = ricevuto.sender;
			int problema = ricevuto.dato;
			nClientInCoda = DIM_CODA_OP-get_val_sem(sem_coda);	//Controllo quanti client ha in coda l'op
			printf("%d : Operatore1°c: INIZIO ho in coda :%d clienti<--\n",getpid(),nClientInCoda);fflush(stdout);
			printf("%d : Operatore1°c: Servo client: %d, richiesta :%d\n",getpid(),client,problema);fflush(stdout);
			risolvi_problema(problema);		//Risolve il problema e dorme
			printf("%d : Operatore1°c: Invio la soluzione al client: %d\n",getpid(),client);fflush(stdout);
			op_coda_invia_soluzione(client);		//Risponde ho risolto il problemaKEY
			printf("%d : Operatore1°c: Client liquidato incremento il semaforo\n",getpid());fflush(stdout);
			nClientInCoda = DIM_CODA_OP-get_val_sem(sem_coda);	//Controllo quanti client ha in coda l'op
			printf("%d : Operatore1°c: Ho in coda :%d clienti\n",getpid(),nClientInCoda);fflush(stdout);
			s_signal(sem_coda);	//Lascio spazio ad un'altro processo
			//pausa();//Per ora nessun operatore va in pausa	
		}
		else
		{
			if(nMessInCoda>0)
			{//2° Caso
				if(next_client(&ricevuto) == -1)   //Serve per prelevare il messaggio del cliente
				{
					printf("%d : Operatore2°c: CONTINUEEEEEEEEEEEEEEEE\n",getpid());fflush(stdout);
					continue;
				}
				printf("%d : Operatore2°c: Inizio sequenza operazioni\n",getpid());fflush(stdout);
				int client = ricevuto.sender;
				int problema = ricevuto.dato;
				printf("%d : Operatore2°c: Servo client: %d, richiesta :%d\n",getpid(),client,problema);fflush(stdout);
				risolvi_problema(problema);		//Risolve il problema e dorme
				printf("%d : Operatore2°c: Invio la soluzione al client: %d\n",getpid(),client);fflush(stdout);
				op_coda_invia_soluzione(client);		//Risponde ho risolto il problema
				printf("%d : Operatore2°c: Client liquidato decremento nMessInCoda il semaforo\n",getpid());fflush(stdout);
				nMessInCoda--;
				printf("%d : Operatore2°c: Ho in coda :%d clienti \n",getpid(),nMessInCoda);fflush(stdout);
				//Non faccio la signal, così gli altri processi restano fuori
				
				if(nMessInCoda == 0)
				{//Reimposto la dimensione della coda
					esitoSet = set_semaforo(sem_coda, DIM_CODA_OP);
					printf("%d : Operatore2°c Semaforo reimpostato! esito : %d, valore :%d\n",getpid(),esitoSet,DIM_CODA_OP);
				}
			}
			else
			{//3° Caso
				if(next_client(&ricevuto) == -1)//Serve per prelevare il messaggio del cliente
				{
					printf("%d : Operatore3°c: CONTINUEEEEEEEEEEEEEEEE\n",getpid());fflush(stdout);
					continue;
				}
				printf("%d : Operatore3°c: Inizio sequenza operazioni\n",getpid());fflush(stdout);
				int client = ricevuto.sender;
				int problema = ricevuto.dato;
				printf("%d : Operatore3°c: Servo client: %d, richiesta :%d\n",getpid(),client,problema);fflush(stdout);
				//Non risolvo nemmeno il problema, invio la segnalazione che sono chiuso
				op_coda_invia_soluzione_CHIUSO(client);
				printf("%d : Operatore3°c: Client liquidato incremento il semaforo\n",getpid());fflush(stdout);
				nClientInCoda = DIM_CODA_OP-get_val_sem(sem_coda);	//Controllo quanti client ha in coda l'op
				printf("%d : Operatore3°c: Ho in coda :%d clienti\n",getpid(),nClientInCoda);fflush(stdout);
				s_signal(sem_coda);	//Lascio spazio ad un'altro processo
			}
		}
		stampaLog("************************************************\n");
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
	return op_coda_ricevi_collega(messCliente, codat);  //Serve per prendere il mess dalla coda scelta		
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
	/*s_wait(sem_stato);
	
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
	return 1;//Riprendo a lavorare*/
}

void cambiatoStatoHD(int signum)
{
	printf("%d : Ho ricevuto il segnale che è cambiato lo stato HD\n",getpid());
	//Conto quanti client ho in coda che devono essere serviti
	nMessInCoda = DIM_CODA_OP-get_val_sem(sem_coda);
	statoHD -= statoHD;

}
