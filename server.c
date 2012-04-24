#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "costanti.h"
#include "miacoda_serv.h"
#include "operatore.h"
#include "util.h"

int coda;	//Indica l'id della coda dell'helpdesk
int continua = 1; //Indica se l'helpdesk deve smettere di lavorare
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
			printf("\nIstanziato %d ° operatore, pid: %d\n", i, padre);
			fflush(stdout);
		}
	}
	
	
	//Creo la coda dell'HelpDesk
	
	
	printf("\nL'id della coda è: %d\n", coda); fflush(stdout);
	s_coda_ini();
	printf("\nL'id della coda è: %d\n", coda); fflush(stdout);
	s_coda_elimina();
	printf("\nL'id della coda è: %d\n", coda); fflush(stdout);
	
	signal(SIGINT, interrompi);
	
	while(continua){;}
	
	for(i=0; i<MAX_N_OP; i++)
		wait(0);
	getchar();
	return 0;
}

void interrompi(int s){
	int i;
	log("Ricevuto sigint");
	for(i=0; i < MAX_N_OP; i++){
		kill(operatori->lista[i], SIGINT);
		log("invio kill a " + i);
	}
	continua = 0;
}
