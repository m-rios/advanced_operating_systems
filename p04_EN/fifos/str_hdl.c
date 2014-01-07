#include "str_hdl.h"

void concatenate(char all[SIZE], char half1[SIZE_HALF], char half2[SIZE_HALF])
{
	strcpy(all, half1);
	strcat(all, half2);
}

void split(char all[SIZE], char half1[SIZE_HALF], char half2[SIZE_HALF])
{
	int a;

	a = strlen(all) / 2;

	strncpy(half1, all, a);
	half1[a] = '\0';

	strcpy(half2, all+a);
}