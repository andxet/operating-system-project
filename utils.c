//
//  utils.c
//  repository
//
//  Created by Andrea Peretti on 31/05/11.
//  Copyright 2011 Università degli studi di Torino. All rights reserved.
//

#include "utils.h"
#include <stdio.h> 
#include <sys/types.h> 
#include <dirent.h> 

int count_file_in_folder(const char * path){
	int count = 0; 
	DIR *d; 
	if( (d = opendir(path)) != NULL) 
	{ 
		for(;  readdir(d) != NULL; count++); 
		closedir(d);
		return count -2; 
	} 
	else
		return -1;	
}

int folder_exist(const char * path){
	DIR *d; 
	if( (d = opendir(path)) == NULL) 
		return 0;
	closedir(d);
	return 1;
}