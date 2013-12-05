#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/uio.h>
#include <string.h>
#include <stdlib.h>
#include "readchar_R.h"

int main()
{
	char* _exit;
	char* cinbuffer;
	int _fd = open("testfile",O_RDWR);
	char _test = readCharacter(_fd,15);
	printf("%c\n",_test );


	return 0;
}