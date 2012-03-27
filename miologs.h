/*
 *  miologs.h
 *  repository
 *
 *  Created by Andrea Peretti on 19/01/11.
 *  Copyright 2011 Università degli studi di Torino. All rights reserved.
 *
 */

#include <sys/ipc.h>
#include <sys/shm.h>

#include "log.h"

#define L_KEY 300

miolog s_buf_ini(char * nome_log);
int s_buf_rimuovi();