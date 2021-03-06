/*############################################################
 ##         -= Progetto di Sistemi Operativi =-             ##
 ## --------------------------------------------------------##
 ##  File:	       costanti.h                               ##
 ##  Created by:	   Fiori, Peretti, Polto                ##
 ##                                                         ##
 ###########################################################*/

#ifndef costanti
#define DEBUG 1	//Serve per le stampe di debug :1: attivo, 0 no
#define LIMITA_PROCESSI 1 // Serve per limitare i processi client attivi
#define MAX_CLIENTI_GENERATI 15	//Se è attivato il limitatore di processi indica quanti client al max avere
#define SEM_PRINT 777	//Semaforo per la gestione dell'oputput

#define STATO_INIZIALE_HD 1	//Se parte in negativo potrebbe dare problemi in operatore

#define MAX_N_OP  3 // Numero massimo di operatori che vengono creati dall'helpdesk
#define DIM_CODA_OP 3 // Dimensione della coda di ogni operatore
					   //#define STATO_HELPDESK 0 //Indica se l'helpdesk è aperto (true) o chiuso (false)
#define DURATA_GIORNO 30 //Tempo (secondi) in cui l'helpdesk è attivo
#define DURATA_NOTTE 30 // Tempo (secondi) in cui l'helpdesk è disattivato

#define CHIUSO 0
#define FALLIMENTO 1
#define APERTO 2

#define MAX_FALLIMENTI_HELPDESK 1

//Costranti per gli operatori
#define OP_PROB_PAUSA 5 //Ho una probabilita' su OP_PROB_PAUSA di andare in pausa, percio' 1=100%, 2=50% 
#define OP_SEC_PAUSA 10 //Secondi di pausa

#define KEY_STATO_OP 998 //Chiave della memoria condivisa stato_helpdesk

/////////////////////// provenienti da coda.h ////////////////////////
//Viene definita la chiave della coda:
//999 per il server di spmistamento
#define SEM_HD 888
#define MAX_ATTESA 10 //Dimensione della coda di attesa

//Definizione dei destinatari (tipo del messaggio, da assegnare al campo long del messaggio)
#define M_SERVER 100 //Server
					 //Per i processi client si userà il loro pid.


//Tipo di aiuto richiesto all'helpdesk
#define N_MAX_RICH 4

//Risposta alla richiesta da parte dell'helpdesk
#define OP_SOLUZIONE 22
#define OP_SOLUZIONE_CHIUSO 99		//Rispondo 99 ai client che si sono addormentati sul semaforo dell'op perchè aveva la coda piena e nel mentre l'HD è stato chiuso! 

//Vettore delle chiavi delle code degli operatori
//int code[DIM_CODA_OP] = {1000, 1001, 1002, 1003
#define KEY_START 1000

#define costanti
#endif
