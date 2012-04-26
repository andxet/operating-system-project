/*###############################################################################
##						-= Progetto di Sistemi Operativi =-					 	          ##
## --------------------------------------------------------------------------- ##
##  File:	       	operazioni_client.c                                       ##
##  Created by:	   Fiori, Peretti, Polto                                     ##
## --------------------------------------------------------------------------- ##
##  Descrizione:    Descrizione del file                                       ##
##                                                                             ##
###############################################################################*/

#include <stdio.h>
#include "costanti.h"
#include "stato_helpdesk.h"
#include "semafori.h"
#include "util.h"

extern stato_helpdesk stato_hd;

int avviaClient()
{
	/* Il client deve verificare lo stato dell' HD per sapere se inviare o no la richiesta
	 * Se aperto fare un random e inviare la richiesta
	*/
	if(verificaHD())
	{//HelpDesk aperto
		int keyOpScelto = KEY_START + gen_rand(MAX_N_OP);	//Decido in modo random a che operatore collegarmi
		//Vado al suo semaforo
		
		
		//Deposito il messaggio nella coda
		
		
		//Lascio posto per altri
	}
	else
	{//HelpDesk chiuso
		stampaLog("HelpDesk chiuso..");
		exit(0);
	}
	
}
int verificaHD()//Verifica se HD è aperto o no
{
	//Mi collego alla memoria condivisa e controllo il valore, se è aperto o no HD
	if(stato_hd->aperto <= 1)
		return 0;//CHIUSO
	else
		return 1;//APERTO
	
}
int inviaRichiesta(int numOp);//Inserisce la richiesta d' aiuto nella coda dell'operatore numOp
