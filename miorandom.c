//
//  miorandom.c
//  helpdesk
//
//  Created by Andrea Peretti on 12/04/12.
//  Copyright (c) 2012 Università degli studi di Torino. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "miorandom.h"

int gen_rand(int n)
/* returns random number in range of 0 to 99 */
{
	return random(n);
}