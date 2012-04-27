/*###############################################################################
##						-= Progetto di Sistemi Operativi =-					 	          ##
## --------------------------------------------------------------------------- ##
##  File:	       	operazioni_client.h                                       ##
##  Created by:	   Fiori, Peretti, Polto                                     ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include "costanti.h"

int avviaClient();
int verificaHD();//Verifica se HD è aperto o no
int inviaRichiesta(int numOp);//Inserisce la richiesta d' aiuto nella coda dell'operatore numOp
