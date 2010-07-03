#ifndef FILEHANDLING
#define FILEHANDLING


#include "../../lib/global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readfile(unsigned char **,unsigned long int *, const char *);
void writefile(char *,unsigned long int , const char *);
void appendfile(unsigned char *,unsigned long int , const char *);

#endif
