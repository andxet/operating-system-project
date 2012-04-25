#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "costanti.h"
#include "operatore.h"
#include "util.h"

int coda;	//Indica l'id della coda dell'helpdesk
int eseguiProgramma = 1; //Se 1 gira, altrimenti chiude tutto
int key, semid; //Variabili pr la coda
int sucessivo;
stato_helpdesk stato_hd;
semaforo lista_sem;

void interrompi(int s);
void chiudi(int s);

int main()
{
	int i;
	pid_t padre;
	//Creo la lista degli operatori
	if(stato_ini() < 0)
		log("Impossibile creare la memoria per salvare l'elenco degli operatori");
	
	signal(SIGINT, interrompi);
	signal(SIGALRM, chiudi);
	
	//Creo i vari operatori
	for (i=0; i < MAX_N_OP; i++)
	{		
		padre = fork();
		
		if (!padre) {//	codice proc. figlio
			log("Avvio");
			avvia(i);
			log(sprintf("Errore nel %d ° operatore, pid: %d\n, chiave risorse ipc %d", i, getpid(), KEY_START+i));
			exit(0);
		}
		
		else {
			printf("Server : Istanziato %d ° operatore, pid: %d, chiave risorse ipc prevista: %d", i, padre, KEY_START+i);
			fflush(stdout);
		}
	}
	
	
	while(stato_hd->aperto != FALLIMENTO){
		;//Aspetta che succeda qualcosa.
		}
	log("Ricevuto il segnale di terminazione, aspetto che gli operatori finiscano.");
	
	for(i=0; i<MAX_N_OP; i++)
		wait(0);
	
	log("Helpdesk chiuso");
	
	getchar();
	return 0;
}

void interrompi(int s){
	log("Ricevuto sigint");
	stato_hd->aperto = FALLIMENTO;
}

void chiudi(int s){
	if(stato_hd->aperto == APERTO){
		stato_hd->aperto = CHIUSO;
		alarm(DURATA_NOTTE);
	}
	else{
		stato_hd->aperto = APERTO;
		alarm(DURATA_GIORNO);
	}
	
}
