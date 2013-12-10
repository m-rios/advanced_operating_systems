#include "commands.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char* ls = myls(".",NULL);
	printf("%s\n",ls);
	return 0;
}



