//
//  mieifile.c
//  repository
//
//  Created by Andrea Peretti on 12/04/11.
//  Copyright 2011 Università degli studi di Torino. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "mieifile.h"

int file_end(FILE * miofile){
	return feof(miofile);
}

int file_nextinstr(FILE * miofile, int * is_instr){
	int istr;
	if(!fscanf(miofile, "%d", &istr))
		instr_non_attesa();
	return istr;
}

int file_nextint(FILE * miofile){
	int intero;
	if(!fscanf(miofile, "%d", &intero))
		instr_non_attesa();
	return intero;
}

char * file_nextstringa(FILE * miofile){
	char * nome = (char * ) malloc(sizeof(char) * L_STRINGA);
	//char * nome;
	if(!fscanf(miofile, "%s", nome))
		instr_non_attesa();
	return nome;
}

float file_nextfloat(FILE * miofile){
	float dato;
	if(!fscanf(miofile, "%fd", &dato))
		instr_non_attesa();
	return dato;
}

void file_rimuovi(FILE * miofile){
	fflush(miofile);
	fclose(miofile);
	miofile = 0;
}

int file_scriviint(FILE * miofile, int dato){
	return fprintf(miofile, "%d\n", dato);
}

int file_scrivistringa(FILE * miofile, char * stringa){
	return fprintf(miofile, "%s\n", stringa);
}

int file_scrivifloat(FILE * miofile, float dato){
	return fprintf(miofile, "%fd\n", dato);
}