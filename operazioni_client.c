/*###############################################################################
##						-= Progetto di Sistemi Operativi =-					 	          ##
## --------------------------------------------------------------------------- ##
##  File:	       	operazioni_client.c                                       ##
##  Created by:	   Fiori, Peretti, Polto                                     ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include <stdio.h>
#include <signal.h>

#include "costanti.h"
#include "stato_helpdesk.h"
#include "semafori.h"
#include "util.h"
#include "miacoda_cli.h"

stato_helpdesk stato_hd;

semaforo semHelpdesk;

int key, coda;

/*
	Valori di ritorno :
		-Se la coda è chiusa : 10
		-Se HelpDesk chiuso  : 20
		-Se Operatore risponde sbagliato : 30
		-Tutto ok : 0
*/
int avviaClient(){

	/* Il client deve verificare lo stato dell' HD per sapere se inviare o no la richiesta
	 * Se aperto fare un random e inviare la richiesta
	*/

	//stampaLog("Client avviato");
	signal(SIGINT, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	stampaLog("************************************************");
	printf("%d : Avviato Cliente\n",getpid()); fflush(stdout);
	
	int stato = verificaHD();
	if(stato == -1)
		exit(10);//Errore nel collegarsi alle risorse IPC. Il server è avviato?
	if(stato == 0)
		exit(20);//L'helpdesk è chiuso.	

	srand((unsigned) time(NULL));//Inizializzo il motore per la creazione di numeri casuali
	key = KEY_START + gen_rand(MAX_N_OP);	//Decido in modo random a che operatore collegarmi
	printf("%d : Cliente mi collego all'opKey %d\n",getpid(),key); fflush(stdout);
	//Vado al suo semaforo
	semaforo semOpScelto = collega_semaforo(key);
s_wait(key);
	//Ho ottenuto l'accesso, mi collego alla coda e deposito il messaggio
	int esitoAggancio = c_coda_aggancia();
	if (esitoAggancio < 0){
		s_signal(key);
		exit(10);
	}
		
	int richiesta = gen_rand(N_MAX_RICH);
	printf("%d : Mi collego all'opKey : %d , con richiesta : %d\n",getpid(),key,richiesta); fflush(stdout);
	c_coda_invia_rich(richiesta);
	int risposta = c_coda_attendi_op(); //Attendo che l'operatore svolga la mia richiesta
	if(risposta != 0){
		printf("%d : L'operatore: %d ha risposto NON VALIDO\n",getpid(),richiesta); fflush(stdout);
		exit(30);//L'operatore è ubriaco?
	}
	else
		printf("%d : L'operatore: %d Risposta OK\n",getpid(),richiesta); fflush(stdout);
	//Lascio posto per altri
	//s_signal(key); -> Lo fa già l'operatore
	printf("%d : Bye...\n",getpid()); fflush(stdout);
	stampaLog("************************************************");	
	exit(0);
}


int verificaHD()//Verifica se HD è aperto o no
{
	//Mi collego alla memoria condivisa e controllo il valore, se è aperto o no HD
	semHelpdesk = collega_semaforo(SEM_HD);
	
	if(stato_aggancia() == -1 || stato_hd < 0 || semHelpdesk < 0)
	{
		stampaLog("Errore -1");
		return -1;//Errore nel collegarsi alle risorse
				  //s_wait(SEM_HD);
	}
	
	if(stato_hd->aperto == CHIUSO || stato_hd->aperto == FALLIMENTO)
	{
		printf("%d -> Cliente non ho avuto risposta HD chiuso\n",getpid()); fflush(stdout);
		//stampaLog("Errore 0");
		return 0;
	}
	else
	{
		stampaLog("Collegato correttamente");
		return 1;//APERTO
				 //s_signal(SEM_HD);
	}


}
