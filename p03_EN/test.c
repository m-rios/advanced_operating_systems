#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/uio.h>
#include <string.h>
#include <stdlib.h>
#include "readchar_R.h"
#include "count_M.h"

int main()
{
	char* _exit;
	char* cinbuffer;
	int _fd = open("testfile",O_RDWR);
	int _nChar = countCharacters(_fd,'a');
	printf("%d\n",_nChar);
	return 0;
}