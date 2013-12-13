#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "readchar_R.h"
#include "count_M.h"

int main(int argc, char const *argv[])
{
	if (argc != 4)
	{
		printf("incorrect number of parameters\n");
		return 0;
	}

	if (strlen(argv[3]) != 1)
	{
		printf("invalid parameter <%s>, must be a char\n",argv[3]);
		return 0;
	}

	//get parameters
	const char* _path = argv[2];
	char _input = argv[3][0];
	int _nChar = 0;

	//open file
	int _fd = open(_path,O_RDONLY);
	if (_fd == -1)
	{
		printf("File doesn't exists or is unaccesible\n");
		return 0;
	}

	//parse mode
	if (strcmp(argv[1],"R") == 0) // call to readchar in a loop
	{
		int i;
		int _fileSize = lseek(_fd,0,SEEK_END);
		for (i=0; i < _fileSize; ++i)
		{
			if (readCharacter(_fd,i) == _input)
				_nChar++;
		}
	}else if (strcmp(argv[1],"M") == 0)//call to countM
	{
		_nChar = countCharacters(_fd,_input);
	}else
	{
		printf("Parameter <%s> unknown\n",argv[1]);
		return 0;
	}

	printf("%d\n",_nChar);

	if (close(_fd)!=0)
		perror("Problem closing file");

	return 0;
}