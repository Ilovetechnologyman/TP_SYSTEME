#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

#ifdef DEBUG
#define DEBUG_PRINT(msg) printf("DEBUG: %s\n", msg)
#else
#define DEBUG_PRINT(msg) // Ne rien faire
#endif

#endif 

