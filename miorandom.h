//
//  miorandom.h
//  helpdesk
//
//  Created by Andrea Peretti on 12/04/12.
//  Copyright (c) 2012 Università degli studi di Torino. All rights reserved.
//

#include <time.h>

#ifndef helpdesk_miorandom_h
#define helpdesk_miorandom_h

#define random(x) rand() % x
#define randomize srand((unsigned)time(NULL))

int gen_rand(int n);

#endif
