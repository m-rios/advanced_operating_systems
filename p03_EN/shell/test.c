#include "commands.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	//mycat test
	char* _content = mycat("testFile");
	if (_content == '\0')
	{
		printf("NULL2\n");
	}
	printf("%s\n", _content);
	//myls test
	/*char* ls = myls(".",NULL);
	printf("%s\n",ls);
	*/
	return 0;
}



