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
			log("Dopo avvio");
			exit(0);
		}
		
		else {
			printf("Server : Istanziato %d ° operatore, pid: %d\n", i, padre);
			//printf("Istanziato %d ° operatore, pid: %d\n", i, padre);
			fflush(stdout);
			operatori->lista[i] = padre;//Inserisco l'id del figlio alla lista
		}
	}
	
	
	while(eseguiProgramma)	{
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
	int i;
	log("Ricevuto sigint");
	for(i=0; i < MAX_N_OP; i++){
		if(operatori->lista[i]==-1)//Se viene interrotto mentre sta generando ancora i client
			continue;//Serve per saltare tutte le istruzioni sotto e tornare in cima al for
		kill(operatori->lista[i], SIGINT);
		log("invio kill a " + i);
	}
	eseguiProgramma = 0;
}

void chiudi(int s){
	stato_hd->aperto = 1-stato_hd->aperto;
}
