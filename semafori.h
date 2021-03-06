/*###########################################################
 ##         -= Progetto di Sistemi Operativi =-             ##
 ## --------------------------------------------------------##
 ##  File:	       semafori.h                               ##
 ##  Created by:	   Fiori, Peretti, Polto                ##
 ##                                                         ##
 ###########################################################*/


//TODO: Decidere se mantenere extern o lasciarlo all'interno di questo programma

#ifndef semafori

typedef int semaforo;

#define S_READ	0
#define S_WRITE 1

//Creazione e rimozione
int crea_semaforo(int key);//Restituisce semaforo di KEY
int collega_semaforo(int key);//Si aggancia a semaforo di KEY

//Operazioni su semafori
int s_wait(int semid);
int s_signal(int semid);
int s_wait0(int semid);
int rimuovi_sem(int semid);
int set_semaforo(int semid, int val);

int get_val_sem(int semid);

#define semafori
#endif
