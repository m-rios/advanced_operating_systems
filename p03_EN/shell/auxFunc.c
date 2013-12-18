#include "auxFunc.h"

void printPrompt(char * cwd, size_t len)
{
	getcwd(cwd, len);
	printf("%s->$ ",cwd);
}

int callInternal(command* C, char* homeDir)
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
	else if (strcmp(C->argv[0],"mypwd") == 0)
	{
		if (C->argc > 1)
			printf("Incorrect usage of mypwd\n");
		else
		{		
			char* pwd = mypwd();
			printf("%s\n",pwd);
			free(pwd);
		}
	}
	else if (strcmp(C->argv[0],"mymkdir") == 0)
	{
		if (C->argc < 2)
			printf("missing argument\n");
		else if (C->argc > 2)
			printf("Incorrect usage of mymkdir\n");
		else
			mymkdir(C->argv[1]);
	}
	else if (strcmp(C->argv[0],"myrmdir") == 0)
	{
		if (C->argc < 2)
			printf("missing argument\n");
		else if (C->argc > 2)
			printf("Incorrect usage of mymkdir\n");
		else
			myrmdir(C->argv[1]);	
	}
	else if (strcmp(C->argv[0],"mycd") == 0)
	{
		if (C->argc >2)
			printf("Incorrect usage of mycd\n");
		else if (C-argc = 2)
			mycd(argc[1])
		else
			mycd(homeDir);
	}
	else
		printf("command not found: %s\n",C->argv[0]);
	return 0;
}