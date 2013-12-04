#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/uio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char* _exit;
	char* cinbuffer;
	int _fd = open("testfile",O_RDWR);
	int _sizeFile = read(_fd,&cinbuffer,5);
	int _bytesW = write(_fd,&cinbuffer,sizeof(cinbuffer));
	printf("%d\n",_sizeFile );
	printf("%s\n", cinbuffer);
	scanf("%s",_exit);
	return 0;
}