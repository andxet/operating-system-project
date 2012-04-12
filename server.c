#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "costanti.h"
#include "miacoda_serv.h"
//#include "operatore.h" lo sta facendo il buon peret

int coda;	//Indica l'id della coda dell'helpdesk

servi(int num)
{
	printf("Operatore : %d, pid : %d \n",num,getpid());
	sleep (10);
	printf("Operatore : %d --> FINE\n",num);
	exit(0);
}


main()
{
	int i;
	pid_t padre;
	//Creo i vari operatori
	for (i=0; i < MAX_N_OP; )
	{		
		padre = fork();
		
		if (!padre) {
			//	codice proc. figlio
			servi(i);
		}
		else
		{
			printf("Istanziato %d ° operatore, pid: %d\n",i, padre);
			i++;
			fflush(stdout);
		}
	}
	
	//Creo la coda dell'HelpDesk
	
	coda = s_coda_ini();
}
