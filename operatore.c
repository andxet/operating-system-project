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

int opPrecedente();
int pausa();
int next_client();

void cambiatoStatoHD(int signum);
void risolvi_problema(int problema);
void licenzia(int s);

stato_helpdesk stato_hd;

semaforo sem_coda;
semaforo sem_stato;
semaforo sem_op_prec;

int op; //Numero dell'operatore
int key;	//Chiave delle sue IPC
//float tempistiche[N_MAX_RICH] = {0.100, 0.050, 0.500, 0.150}; //Secondi di attesa
float tempistiche[N_MAX_RICH] = {1, 1, 1, 1}; //Secondi di attesa

int collega_gia_servito; //Booleano che indica se il collega in pausa è già stato servito
int coda; //Coda dell'operatore
int statoHD = STATO_INIZIALE_HD;
int nMessInCoda = 0;
int nClientInCoda = 0;

char * messaggio;


int avvia(int idOp){  //avvia l'operatore
	avvia_motore_rand();//Inizializzo il motore random
	signal(SIGUSR1,cambiatoStatoHD);
	signal(SIGINT, licenzia);
	op = idOp;
	key = KEY_START + op;
	printf("%d : Operatore: avviato key :%d\n",getpid(),key);fflush(stdout);
	
	//Aggangio alle risorse IPC dell'helpdesk
	if(stato_aggancia() == -1){//Controllo per collegarsi alla memoria condivisa dell'helpdesk
		printf("Errore nel collegarsi alla coda");
		exit(-1);
	}
	if((long)stato_hd == -1){//Controllo 
		printf("Stato helpdesk è a -1!");
		exit(-1);
	}
	sem_stato = collega_semaforo(SEM_HD);
	if(sem_stato == -1){
		printf("Il semaforo di stato helpdesk è a -1!");
		exit(-1);
	}
	if(sem_coda == -1){
		printf("Il semaforo della coda è a -1!");
		exit(-1);
	}
	
	
	sem_coda = crea_semaforo(key);	//Semaforo della coda dell'operatore
	if(op_coda_ini() < 0 || sem_coda < 0){
		printf("Errore nell'allocazione delle risorse IPC");
		exit(-1);
	}
	int esitoSet = set_semaforo(sem_coda, DIM_CODA_OP);
	nClientInCoda = get_val_sem(sem_coda);

	stampaLog("Operatore: pronto a servire");
	
	collega_gia_servito = 0;
	while(stato_hd->aperto != FALLIMENTO){
		coda_messaggio ricevuto;
		/* Differenzio i 3 casi :
				- 1° HD Aperto
				- 2° HD Chiuso, ma l'op ha ancora da servire alcuni clienti
				- 3° HD Chiso, Op ha risposto a tutte i clienti, deve rispondere negativamente a quelli che entrano
		*/
		if(stato_hd->aperto == APERTO)
		{//1°Caso
			if(next_client(&ricevuto) == -1)   //Serve per prelevare il messaggio del cliente
			{
				continue;
			}
			int client = ricevuto.sender;
			int problema = ricevuto.dato;
			sprintf(messaggio, "%s%d : Operatore1°c: Servo client: %d, richiesta :%d\n",messaggio,getpid(),client,problema);
			risolvi_problema(problema);		//Risolve il problema e dorme
			sprintf(messaggio, "%s%d : Operatore1°c: Invio la soluzione al client: %d\n",messaggio,getpid(),client);
			op_coda_invia_soluzione(client);		//Risponde ho risolto il problemaKEY
			
			if(collega_gia_servito == 0)//Controllo se sto servendo un mio cliente o quello del collega
			{//Sto servendo un mio cliente
				//nClientInCoda = DIM_CODA_OP-get_val_sem(sem_coda);	//Controllo quanti client ha in coda l'op
				//sprintf(messaggio, "%s\n%d : Operatore1°c: Ho in coda :%d clienti\n",messaggio,getpid(),nClientInCoda);
				s_signal(sem_coda);	//Lascio spazio ad un'altro processo
			}
			else
			{//Sto servendo un cliente del mio collega
				//nClientInCoda = DIM_CODA_OP-get_val_sem(sem_coda);	//Controllo quanti client ha in coda l'op
				//sprintf(messaggio, "%s%d : Operatore1°c: Ho servito il cliente del mio collega faccio la signal sulla sua coda\n",messaggio,getpid());
				s_signal(sem_op_prec);	//Faccio la signal sulla coda del mio collega
			}
			//End controlli
			stampaLog(messaggio);
			pausa();//Vuole andare in pausa
		}
		else
		{
			if(nMessInCoda>0)
			{//2° Caso
				if(next_client(&ricevuto) == -1)   //Serve per prelevare il messaggio del cliente
				{
					continue;
				}
//				printf("%d : Operatore2°c: Inizio sequenza operazioni\n",getpid());fflush(stdout);
				int client = ricevuto.sender;
				int problema = ricevuto.dato;
				sprintf(messaggio, "%s%d : Operatore2°c: Servo client: %d, richiesta :%d\n",messaggio,getpid(),client,problema);
				risolvi_problema(problema);		//Risolve il problema e dorme
				sprintf(messaggio, "%s%d : Operatore2°c: Invio la soluzione al client: %d\n",messaggio,getpid(),client);
				op_coda_invia_soluzione(client);		//Risponde ho risolto il problema
				//printf("%d : Operatore2°c: Client liquidato decremento nMessInCoda il semaforo\n",getpid());fflush(stdout);
				nMessInCoda--;
				//printf("%d : Operatore2°c: Ho in coda :%d clienti \n",getpid(),nMessInCoda);fflush(stdout);
				//Non faccio la signal, così gli altri processi restano fuori
				
				if(nMessInCoda == 0)
				{//Reimposto la dimensione della coda
					esitoSet = set_semaforo(sem_coda, DIM_CODA_OP);
					//printf("%d : Operatore2°c Semaforo reimpostato! esito : %d, valore :%d\n",getpid(),esitoSet,DIM_CODA_OP);
				}
				stampaLog(messaggio);
			}
			else
			{//3° Caso
				if(next_client(&ricevuto) == -1)
				{
					continue;
				}
//				printf("%d : Operatore3°c: Inizio sequenza operazioni\n",getpid());fflush(stdout);
				int client = ricevuto.sender;
				int problema = ricevuto.dato;
				sprintf(messaggio, "%s%d : Operatore3°c: Servo client: %d, richiesta :%d\n",messaggio,getpid(),client,problema);
				//Non risolvo nemmeno il problema, invio la segnalazione che sono chiuso
				op_coda_invia_soluzione_CHIUSO(client);
				sprintf(messaggio, "%s%d : Operatore3°c: Client liquidato, sono chiuso %d\n",messaggio,getpid());
				//nClientInCoda = DIM_CODA_OP-get_val_sem(sem_coda);	//Controllo quanti client ha in coda l'op
				//printf("%d : Operatore3°c: Ho in coda :%d clienti\n",getpid(),nClientInCoda);fflush(stdout);
				s_signal(sem_coda);	//Lascio spazio ad un'altro processo
				stampaLog(messaggio);
			}
		}
		//stampaLog("************************************************\n");
	}
	stampaLog("Helpdesk in chiusura, uscita.");
	exit(0);
}

int next_client(coda_messaggio * messCliente){
	int codat;
	s_wait(sem_stato);//Serve per accedere alla memoria dell HD e controllare che OP è in pausa
	if(stato_hd->inPausa != 0 && stato_hd->inPausa == opPrecedente() && !collega_gia_servito)
	{//Se l'operatore precedente è in pausa e non ho già servito un suo cliente, estraggo un cliente dalla sua lista
	
		//Devo servire un cliente del mio collega, collego che effettivamente abbia messaggi sulla coda, altrimenti mi metto ad aspettare per niente
		//Controllo il suo semaforo così vedo subito se ha dei messaggi o no :D
		sem_op_prec = collega_semaforo(opPrecedente());//Mi collego al semaforo dell'operatore precedente
		nClientInCoda = DIM_CODA_OP-get_val_sem(sem_op_prec);
		if(nClientInCoda <= 0)
		{//Non ho nessun client da servire sulla coda del collega, continuo con la mia coda
			//Ho copiato il codice sotto
			codat = coda;
		 	collega_gia_servito = 0;
		 	sprintf(messaggio, "Operatore %d: Servo un mio cliente.\n", id);
		}
		else
		{
			codat = coda_aggancia(opPrecedente());
			sprintf(messaggio, "Operatore %d: Servo un cliente del collega in pausa.\n", id);
			collega_gia_servito = 1;
		}
	}
	else
	{
		 codat = coda;
		 collega_gia_servito = 0;
		 sprintf(messaggio, "Operatore %d: Servo un mio cliente.\n", id);
	}
	s_signal(sem_stato);
	return op_coda_ricevi_collega(messCliente, codat);  //Serve per prendere il mess dalla coda scelta		
}

void risolvi_problema(int problema){
	if(problema < 0 || problema > N_MAX_RICH)
		return;
	
	//sprintf(messaggio, "%s\n%d : Operatore: Eseguo la richiesta, dormo :%f\n",messaggio,getpid(),tempistiche[problema]);
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

int pausa(){
	//Faccio un random per vedere se devo andare in pausa
	int probabilita = gen_rand(OP_PROB_PAUSA);	//Decido in modo random se andare in pausa
	
	if(probabilita == 0)
	{//Voglio andare in pausa
		s_wait(sem_stato);//Attendo il mio turno
		int inPausa = stato_inPausa();//return -1 se errore, altrimenti id dell'operatore in pausa
		if (inPausa == 0)
		{//Non ci sono Operatori in pausa, ci vado io :D
			sprintf(messaggio, "Operatore %d: Vado in pausa.\n", id);
			stato_hd->inPausa = KEY_START + op;	//Metto l'id della mia coda nel campo pausa
			s_signal(sem_stato);
			stampaLog(messaggio);
	
				sleep(OP_SEC_PAUSA);	//Eseguo la pausa
	
			s_wait(sem_stato);
			stato_hd->inPausa = 0;
			sprintf(messaggio, "Operatore %d: Torno dalla pausa.\n", id);
			s_signal(sem_stato);
			stampaLog(messaggio);
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
