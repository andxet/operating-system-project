/*
 *  miacodac.h
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

//Funzioni da utilizzare nel server, ossia il disppatcher.
#include "coda.h"

int s_coda_ini(int * coda); //Crea la coda. Se esite, ritorna -2, 
int s_coda_rispondi(int * sender); //Restituisce il pid del client che effettua una richiesta all'helpdesk
int s_invia_rifiuto(int dest); //Invia un messaggio di rifiuto, da usare quando l'helpdesk è chiuso
int s_coda_elimina(int coda); //Elimina la coda il cui id è salvato in coda
int s_coda_elimina_esistente(); //Elimina la coda esistente che utilizza l'id scelto