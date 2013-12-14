#include "auxFunc.h"
#include "parser.h"

printPrompt()
{

}

callInternal(command C)
{
	if (strcmp(C->argv[0],"mycat") == 0)
	{
		if (C->argc == 2)
			mycat(argv[0]);
		else if (C->argc == 1)
			printf("Argument missing\n");
		else if (C->argc > 2)
			printf("Incorrect usage of mycat\n");
	}
	else if (strcmp(C->argv[0],"mycp") == 0)
	{
		if (C->argc == 3)
			mycp(argv[1],argv[2]);
		else if (C->argc == 2)
			printf("Destination needed\n");
		else if (C->argc == 1)
			printf("Source & destination needed\n");
		else
			printf("Incorrect usage of mycp\n");
	}
	else
		printf("command not found: %s\n",argv[0]);
}