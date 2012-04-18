/*###############################################################################
##						-= Progetto di Sistemi Operativi =-			           ##
## --------------------------------------------------------------------------- ##
##  File:	       miacoda_serv.h                                              ##
##  Created by:	   Fiori, Peretti, Polto                                       ##
## --------------------------------------------------------------------------- ##
##  Descrizione:   Header delle classi della coda del server                   ##
##                                                                             ##
###############################################################################*/

//Funzioni da utilizzare nel server, ossia il disppatcher.
#include "coda.h"


extern int coda;

int s_coda_ini(); //Crea la coda. Se esite, ritorna -2, 
int s_coda_rispondi(int * sender); //Restituisce il pid del client che effettua una richiesta all'helpdesk
int s_invia_chiuso(int dest); //Invia un messaggio di rifiuto, da usare quando l'helpdesk è chiuso
int s_invia_occupato(int dest);//Invia un messaggio di rifiuto, da usare quando la coda d'attesa dell'helpdesk è piena
int s_coda_elimina(); //Elimina la coda il cui id è salvato in coda
int s_coda_elimina_esistente(); //Elimina la coda esistente che utilizza l'id scelto