//
//  provasem.c
//  helpdesk
//
//  Created by Andrea Peretti on 26/04/12.
//  Copyright (c) 2012 Università degli studi di Torino. All rights reserved.
//

#include <stdio.h>


#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "semafori.h"

#include "util.h"

int main(){
	semaforo sem = crea_semaforo(500);
	if(sem < 0)
		exit(-1);
	set_semaforo(sem, 5);
	int i;
	for(i=0; i<10; i++){
		int padre = fork();
		if(!padre){
			//semaforo sem2 = collega_semaforo(500);
			semaforo sem2=sem;
			printf("%d\n", sem2);
			if(sem2 < 0){
				stampaLog("Errore con il semaforo.");
				exit(-1);
			}
			stampaLog("Sto per entrare nella regione critica.");
			s_wait(sem2);
			stampaLog("Sono nella sezione critica.");
			sleep(5);
			s_signal(sem2);
			stampaLog("Esco.");
			exit(0);
		}
	}
	for(i=0; i<10; i++){
		wait(0);
	}
	getchar();
	rimuovi_sem(sem);
		
}