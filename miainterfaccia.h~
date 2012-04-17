//
//  miainterfaccia.h
//  repository
//
//  Created by Andrea Peretti on 12/04/11.
//  Copyright 2011 Università degli studi di Torino. All rights reserved.
//

#include <stdio.h>

#ifndef MIAINTERFACCIA

#define L_OPZIONI 80

typedef char * opzione;
typedef struct menu * miomenu;

struct menu{
	char * intestazione;
	int num_opzioni;
	opzione * opzioni;
};

int richiesta(char * domanda);
int accettabilesn(char risposta);
miomenu menu_ini(char * intestazione, int opzioni, ...);
void menu_stampa(miomenu menus);
int menu_chiedi(miomenu menus);
void menu_free(miomenu menu);

#define MIAINTERFACCIA
#endif