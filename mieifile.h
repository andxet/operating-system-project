//
//  mieifile.h
//  repository
//
//  Created by Andrea Peretti on 12/04/11.
//  Copyright 2011 Università degli studi di Torino. All rights reserved.
//

#include <stdio.h>

#define L_STRINGA 30

extern void instr_non_attesa();

int file_end(FILE * miofile);
int file_nextint(FILE * miofile);
char * file_nextstringa(FILE * miofile);
float file_nextfloat(FILE * miofile);
void file_rimuovi(FILE * miofile);
int file_scriviint(FILE * miofile, int dato);
int file_scrivistringa(FILE * miofile, char * stringa);
int file_scrivifloat(FILE * miofile, float dato);
int file_nextinstr(FILE * miofile, int * is_instr);