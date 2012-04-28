#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "costanti.h"
#include "operatore.h"
#include "util.h"

int coda;	//Indica l'id della coda dell'helpdesk
int eseguiProgramma = 1; //Se 1 gira, altrimenti chiude tutto
int key, semid; //Variabili pr la coda
int sucessivo;
int operatori[MAX_N_OP];
stato_helpdesk stato_hd;
semaforo lista_sem;

void interrompi(int s);
void chiudi(int s);

int main()
{
	int i;
	pid_t padre;
	//Creo la lista degli operatori
	lista_sem = crea_semaforo(SEM_HD);
	if(stato_ini() < 0 || lista_sem == -1){
		stampaLog("Impossibile creare la memoria per salvare l'elenco degli operatori");
		exit(-1);
	}
	
	set_semaforo(lista_sem, 1);
	
	signal(SIGINT, interrompi);
	signal(SIGALRM, chiudi);
	
	stampaLog("************************ Istanziato HelpDesk ************************");
	
	//Creo i vari operatori
	for (i=0; i < MAX_N_OP; i++)
	{		
		padre = fork();
		
		if (!padre) {//	codice proc. figlio
			avvia(i);
			printf("%d : Errore nel %d ° operatore, pid: %d, chiave risorse ipc %d\n",getpid(), i, padre, KEY_START+i); fflush(stdout);
			exit(0);
		}
		
		else {
			printf("%d : Istanziato %d° operatore, pid: %d, chiave risorse ipc prevista: %d\n",getpid(), i, padre, KEY_START+i);fflush(stdout);
			//fflush(stdout);
			operatori[i] = padre;
		}
	}
	
	alarm(DURATA_GIORNO);
	
	while(stato_hd->aperto != FALLIMENTO){
		sleep(100);//Aspetta che succeda qualcosa.
	}
	
	//stampaLog("****Ricevuto il segnale di terminazione, aspetto che gli operatori finiscano.****\n");
	
	for(i=0; i<MAX_N_OP; i++)
		wait(0);

	stato_rimuovi();
	stampaLog("************************ Helpdesk chiuso ************************\n");
	return 0;
}

void interrompi(int s){
	stampaLog("*** Ricevuto sigint, inizio procedura di chiusura. ***\n");
	stato_hd->aperto = FALLIMENTO;
	int i = 0;
	for(; i < MAX_N_OP; i++)
		kill(SIGINT, operatori[i]);
}

void chiudi(int s){
/* Inserite wait e Signal per accedere alla memoria */
s_wait(lista_sem);
	if(stato_hd->aperto == APERTO){
		stato_hd->aperto = CHIUSO;
		signal(SIGALRM, chiudi);
		alarm(DURATA_NOTTE);
		stampaLog("\n************************\nCHIUSURA E' NOTTE\n************************\n");
	}
	else{
		stato_hd->aperto = APERTO;
		signal(SIGALRM, chiudi);
		alarm(DURATA_GIORNO);
		stampaLog("\n************************\nAPERTURA E' MATTINO!\n************************\n");
	}
s_signal(lista_sem);	

	
}
