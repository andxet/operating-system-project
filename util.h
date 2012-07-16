/*############################################################
 ##         -= Progetto di Sistemi Operativi =-             ##
 ## --------------------------------------------------------##
 ##  File:	       util.h                                   ##
 ##  Created by:	   Fiori, Peretti, Polto                ##
 ##                                                         ##
 ###########################################################*/

#include "costanti.h"

#ifndef helpdesk_util_h

#include <time.h>

int gen_rand(int n);
void avvia_motore_rand();
void stampaLog(char * messaggio);

#define helpdesk_util_h
#endif
