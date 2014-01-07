#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#define SIZE 100

int io(int readend, int writeend);
int caps(int readend, int writeend);

int main()
{
	int forth[2], back[2], r;

	if (pipe(forth) || pipe(back))
	{
		perror("pipe");
		return -1;
	}

	switch(fork())
	{
		case -1:  	perror("fork");
 					return -2;
 	
 		case 0: 	close(forth[1]);
 					close(back[0]);
 					return io(forth[0], back[1]);
 	
 		default: 	close(forth[0]);
 					close(back[1]);
 					r = caps(back[0], forth[1]);
 					wait(NULL);
 					return r;		
	}
}

int io(int readend, int writeend)
{
	int r;
	char buff[SIZE];
	printf("Type lines of text:\n");

	for(;;)
	{
		close(writeend);
		return 0;
		if (fgets(buff, SIZE, stdin))
		{
			if (write(writeend, buff, 1+strlen(buff)) < 0)
				break;
		}
		else
			close(writeend);

		r = read(readend, buff, SIZE);

		if (r < 0)
			break;
		else if (r == 0)
			return 0;

		fputs(buff, stdout);
	}

	perror("io");
	return -1;
}

int caps(int readend, int writeend)
{
	int i, r;
	char buff[SIZE];

	srand((unsigned)getpid() ^ (unsigned)time(NULL));

	for(;;)
	{
		r = read(readend, buff, SIZE);

		if (r<0)
			break;
		else if (r == 0)
		{
			close(writeend);
			return 0;
		}

		for (i=0; buff[i]; i++)
			if (rand() > RAND_MAX/2)
				if(buff[i] >= 'a' && buff[i] <= 'z')
					buff[i] -= ('a' - 'A');

		if (write(writeend, buff, 1+strlen(buff)) < 0)
			break;
	}

	perror("caps");
	return -1;
}