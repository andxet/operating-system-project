#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "costanti.h"
#include "miacoda_serv.h"
#include "operatore.h"
#include "util.h"

int coda;	//Indica l'id della coda dell'helpdesk
int eseguiProgramma = 1; //Se 1 gira, altrimenti chiude tutto
int aperto = 1; //Indica il giorno o la notte
int key, semid; //Variabili pr la coda
lista_operatori operatori;
semaforo lista_sem;

void interrompi(int s);

int servi2(int num)
{
	printf("Operatore : %d, pid : %d \n",num,getpid());
	sleep (0.1);
	printf("Operatore : %d --> FINE\n",num);
	exit(0);
}


int main()
{
	int i;
	pid_t padre;
	//Creo la lista degli operatori
	if(lista_operatori_ini() < 0)
		log("Impossibile creare la memoria per salvare l'elenco degli operatori");
	
	signal(SIGINT, interrompi);
	
	//Creo i vari operatori
	for (i=0; i < MAX_N_OP; i++)
	{		
		padre = fork();
		
		if (!padre) {
			//	codice proc. figlio

			//avvia(i);
			log("Avvio");
			avvia(i);
			log("Dopo avvio");
			//TODO: SALVARE IN MEM CONDIVISA L'ID(PID) DELL'OPERATORE
			exit(0);
		}
		else
		{
			log("Server : Istanziato %d ° operatore, pid: %d\n", i, padre);
			//printf("Istanziato %d ° operatore, pid: %d\n", i, padre);
			fflush(stdout);
			operatori->lista[i] = padre;//Inserisco l'id del figlio alla lista
		}
	}
	
	
	//Creo la coda dell'HelpDesk <-- Delle richieste, dove si collegano i vari client
	printf("\nL'id della coda è: %d\n", coda); fflush(stdout);
	s_coda_ini();
		
	
	while(aperto)
	{
		
	}
	
	for(i=0; i<MAX_N_OP; i++)
		wait(0);
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
