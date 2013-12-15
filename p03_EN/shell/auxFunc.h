#ifndef _AUXFUNC_H
#define _AUXFUNC_H

#include <string.h>
#include "parser.h"
#include "commands.h"

void printPrompt();
int callInternal(command * C);

#endif