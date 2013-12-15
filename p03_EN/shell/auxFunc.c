#include "auxFunc.h"

void printPrompt(char * cwd, size_t len)
{
	getcwd(cwd, len);
	printf("%s->$ ",cwd);
}

int callInternal(command* C)
{
	if (C->argc == 0)
		return 0;
	else if (strcmp(C->argv[0],"exit") == 0)
		return 1;
	else if (strcmp(C->argv[0],"mycat") == 0)
	{
		if (C->argc == 2)
			printf("%s\n",mycat(C->argv[1]));
		else if (C->argc == 1)
			printf("Argument missing\n");
		else if (C->argc > 2)
			printf("Incorrect usage of mycat\n");
	}
	else if (strcmp(C->argv[0],"mycp") == 0)
	{
		if (C->argc == 3)
			mycp(C->argv[1],C->argv[2]);
		else if (C->argc == 2)
			printf("Destination needed\n");
		else if (C->argc == 1)
			printf("Source & destination needed\n");
		else
			printf("Incorrect usage of mycp\n");
	}
	else
		printf("command not found: %s\n",C->argv[0]);
	return 0;
}