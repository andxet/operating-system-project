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
float tempistiche[N_MAX_RICH] = {3, 3, 3, 3}; //Secondi di attesa

int collega_gia_servito; //Booleano che indica se il collega in pausa è già stato servito

int coda; //Coda dell'operatore
semaforo sem_coda;

stato_helpdesk stato_hd;
semaforo sem_stato;

semaforo sem_op_prec;

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
//printf("%d : Semaforo settato esito : %d, valore :%d\n",getpid(),esitoSet,DIM_CODA_OP);
	int nClientInCoda = get_val_sem(sem_coda);
//	printf("%d : Operatore: Ho settato il mio semaforo a :%d \n",getpid(),nClientInCoda);fflush(stdout);
	
//	printf("%d : Operatore: pronto a servire\n",getpid());fflush(stdout);
	
	collega_gia_servito = 0;
	while(stato_hd->aperto != FALLIMENTO){
		coda_messaggio ricevuto;
		/* Differenzio i 3 casi :
				- 1° HD Aperto
				- 2° HD Chiuso, ma l'op ha ancora da servire alcuni clienti
				- 3° HD Chiso, Op ha risposto a tutte i clienti, deve rispondere negativamente a quelli che entrano
		*/
//		stampaLog("************************************************");
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
//			printf("%d : Operatore1°c: INIZIO ho in coda :%d clienti<--\n",getpid(),nClientInCoda);fflush(stdout);
			printf("%d : Operatore1°c: Servo client: %d, richiesta :%d\n",getpid(),client,problema);fflush(stdout);
			risolvi_problema(problema);		//Risolve il problema e dorme
			printf("%d : Operatore1°c: Invio la soluzione al client: %d\n",getpid(),client);fflush(stdout);
			op_coda_invia_soluzione(client);		//Risponde ho risolto il problemaKEY
//			printf("%d : Operatore1°c: Client liquidato incremento il semaforo\n",getpid());fflush(stdout);
			//Controllo se sto servendo un mio cliente o quello del collega
			if(collega_gia_servito == 0)
			{//Sto servendo un mio cliente
				nClientInCoda = DIM_CODA_OP-get_val_sem(sem_coda);	//Controllo quanti client ha in coda l'op
				printf("%d : Operatore1°c: Ho in coda :%d clienti\n",getpid(),nClientInCoda);fflush(stdout);
				s_signal(sem_coda);	//Lascio spazio ad un'altro processo
			}
			else
			{//Sto servendo un cliente del mio collega
				nClientInCoda = DIM_CODA_OP-get_val_sem(sem_coda);	//Controllo quanti client ha in coda l'op
				printf("%d : Operatore1°c: Ho servito il cliente del mio collega faccio la signal sulla sua coda\n",getpid());fflush(stdout);
				s_signal(sem_op_prec);	//Faccio la signal sulla coda del mio collega
			}
			//End controlli
			
			pausaKikko();//Vuole andare in pausa
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
//				printf("%d : Operatore2°c: Inizio sequenza operazioni\n",getpid());fflush(stdout);
				int client = ricevuto.sender;
				int problema = ricevuto.dato;
				printf("%d : Operatore2°c: Servo client: %d, richiesta :%d\n",getpid(),client,problema);fflush(stdout);
				risolvi_problema(problema);		//Risolve il problema e dorme
//				printf("%d : Operatore2°c: Invio la soluzione al client: %d\n",getpid(),client);fflush(stdout);
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
				if(next_client(&ricevuto) == -1)
				{
					printf("%d : Operatore3°c: CONTINUEEEEEEEEEEEEEEEE\n",getpid());fflush(stdout);
					continue;
				}
//				printf("%d : Operatore3°c: Inizio sequenza operazioni\n",getpid());fflush(stdout);
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
	if(stato_hd->inPausa != 0 && stato_hd->inPausa == opPrecedente() && !collega_gia_servito){//Se l'operatore precedente è in pausa e non ho già servito un suo cliente, estraggo un cliente dalla sua lista
	
		//Devo servire un cliente del mio collega, collego che effettivamente abbia messaggi sulla coda, altrimenti mi metto ad aspettare per niente
		//Controllo il suo semaforo così vedo subito se ha dei messaggi o no :D
		sem_op_prec = collega_semaforo(opPrecedente());//Mi collego al semaforo dell'operatore precedente
		nClientInCoda = DIM_CODA_OP-get_val_sem(sem_op_prec);
		if(nClientInCoda <= 0)
		{//Non ho nessun client da servire sulla coda del collega, continuo con la mia coda
			//Ho copiato il codice sotto
			codat = coda;
		 	collega_gia_servito = 0;
		 	printf("%d : Servo un mio cliente.\n",getpid());fflush(stdout);
		}
		else
		{
			codat = coda_aggancia(opPrecedente());
			printf("%d : Servo un cliente del mio collega in pausa.\n",getpid());fflush(stdout);
			collega_gia_servito = 1;
		}
	}
	else{
		 codat = coda;
		 collega_gia_servito = 0;
		 printf("%d : Servo un mio cliente.\n",getpid());fflush(stdout);
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

int opPrecedente(){//Restituisce la chiave dell'operatore precedente
	return KEY_START + ((op - 1 + MAX_N_OP)%MAX_N_OP);
}

void licenzia(int s){
	coda_rimuovi(coda);//printf("%d: Elimino la coda : %d\n",getpid(),coda);
	rimuovi_sem(sem_coda);//printf("%d: Elimino il semaforo : %d\n",getpid(),sem_coda);
	//printf("%d: Ho eliminato tutto posso morire in pace +_+\n",getpid());	
}

int pausaKikko(){
	//Faccio un random per vedere se devo andare in pausa
	srand((unsigned) time(NULL));//Inizializzo il motore random
	int probabilita = gen_rand(OP_PROB_PAUSA);	//Decido in modo random se andare in pausa
	
	if(probabilita == 0)
	{//Voglio andare in pausa
		s_wait(sem_stato);//Attendo il mio turno
		int inPausa = stato_inPausa();//return -1 se errore, altrimenti id dell'operatore in pausa
		if (inPausa == 0)
		{//Non ci sono Operatori in pausa, ci vado io :D
			stampaLog("");
			printf("\n\n%d : ME NE VADO IN PAUSA \n\n",getpid());fflush(stdout);
			stato_hd->inPausa = KEY_START + op;	//Metto l'id della mia coda nel campo pausa
			s_signal(sem_stato);
	
				sleep(OP_SEC_PAUSA);	//Eseguo la pausa
	
			s_wait(sem_stato);
			stato_hd->inPausa = 0;
			printf("\n\n%d : TORNO DALLA PAUSA\n\n",getpid());fflush(stdout);
			s_signal(sem_stato);
			return 1;//Riprendo a lavorare
		}
		else
		{//Ci sono altri operatori in pausa, non posso andarci :/ , torno a lavorare
			s_signal(sem_stato);
			return 0;
		}
	}
	else
	{//Mi piace lavorare
		return 0;
	}
}

void cambiatoStatoHD(int signum)
{
	printf("%d : Ho ricevuto il segnale che è cambiato lo stato HD\n",getpid());
	//Conto quanti client ho in coda che devono essere serviti
	nMessInCoda = DIM_CODA_OP-get_val_sem(sem_coda);
	//Cambio di stato il valore, 0->1 , 1->0
	//statoHD -= statoHD;	//Modo 1, rischio che vada in -1 se il valore iniziale di statoHD è 0
	statoHD = 1-statoHD;		//In questo modo sono sicuro che il numero resti sempre 0 o 1, anche se lo stato iniziale è 0

}
