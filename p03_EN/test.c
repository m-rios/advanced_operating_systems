#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main()
{
	char* _exit;
	int fd = open("testfile",O_RDWR);
	printf("%d\n",fd );
	scanf("%s",_exit);
	return 0;
}