#ifndef _AUXFUNC_H
#define _AUXFUNC_H

#include <string.h>
#include "parser.h"
#include "commands.h"
#include <stdlib.h>

void printPrompt();
int callInternal(command * C, char* homeDir);

#endif