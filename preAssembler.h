#ifndef _PREASSEMBLER_H
#define _PREASSEMBLER_H

#include "utils.h"
#include "declarations.h"


bool preAssembler(FILE *ipf, char* fileName);

typedef struct macro {
    char name[MAX_MCR];
    char content[MAX_MCR];
} macro;


#endif
