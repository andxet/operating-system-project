//
//  miainterfaccia.c
//  repository
//
//  Created by Andrea Peretti on 12/04/11.
//  Copyright 2011 Università degli studi di Torino. All rights reserved.
//

#include "miainterfaccia.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

int richiesta(char * domanda){
	char risposta;
	
	do{
		printf("%s (S/N)?\n", domanda);
		scanf("%s", &risposta);
	}while(!accettabilesn(risposta));
	switch(risposta){
		case 's':
		case 'S':
			return 1;
		case 'n':
		case 'N':
			return 0;
			
	}
	return -1;
}

int accettabilesn(char risposta){
	return risposta == 'n'
	|| risposta == 'N'
	|| risposta == 'S'
	|| risposta == 's';
}

miomenu menu_ini(char * intestazione, int cont, ...){
	miomenu menum = (miomenu) malloc(sizeof(struct menu));	
	int i;
	menum->intestazione = intestazione;
	menum->num_opzioni = cont;
	menum->opzioni = (opzione *) malloc(sizeof(opzione) * cont);
	va_list opz;
	va_start(opz, cont);	
	for(i = 0; i < cont; i++){
		menum->opzioni[i] = (opzione) malloc(sizeof(opzione) * L_OPZIONI);
		strcpy(menum->opzioni[i], va_arg(opz, opzione));
	}
	va_end(opz);
	return menum;
}

void menu_stampa(miomenu menus){
	printf("%s\n", menus->intestazione);
	int i;
	for(i=0; i < menus->num_opzioni; i++)
		printf("\t%d) %s,\n", i+1, menus->opzioni[i]);
	printf("\t%d) indietro/esci.\n", i + 1);
}

void menu_free(miomenu menu){
	if(!menu)
		return;
	int i;
	for(i = menu->num_opzioni - 1; i > 0 ; i --)
		free(menu->opzioni[i]);
	free(menu);
}

int menu_chiedi(miomenu menus){
	menu_stampa(menus);
	int risp;
	do{
		scanf("%d", &risp);
		if(risp < 1 || risp > menus->num_opzioni + 1){
			printf("Inserire un numero compreso tra 1 e %d.\n", menus->num_opzioni + 1);
			risp = 0;
		}
	}while(risp < 1 || risp > menus->num_opzioni + 1);
	if(risp == menus->num_opzioni + 1)
		return -1;
	else
		return risp;
}