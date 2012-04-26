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
		int key = KEY_START + gen_rand(MAX_N_OP);	//Decido in modo random a che operatore collegarmi
		//Vado al suo semaforo
		semaforo semOpScelto = collega_semaforo(key);
		s_wait(key);
		//Ho ottenuto l'accesso, mi collego alla coda e deposito il messaggio
		int coda;
		c_coda_aggancia();
		
		int richiesta = gen_rand(N_MAX_RICH);
		c_coda_invia_rich(richiesta);
		int risposta = c_coda_attendi_op(); //Attendo che l'operatore svolga la mia richiesta
		if(risposta != 0)
			log("L'OPERATORE MI HA DATO UNA RISPOSTA NON VALIDA...");
		
		//Lascio posto per altri
		s_signal(key);
		
		log("Ho ricevuto la risposta, termino la chiamata!");
		
		exit(0);
	}
	else
	{//HelpDesk chiuso
		log("HelpDesk chiuso..");
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
