#include "cap_trans.h"
int caps(int readend, int writeend)
{
	int i, r;
	char buff[SIZE];

	srand((unsigned)getpid() ^ (unsigned) time(NULL));

	while(1)
	{
		printf("i vuelta a empezar %d\n", getpid());
		r = read(readend, buff, SIZE);

		printf("R of %d: %d\n", getpid(), r);

		if (r< 0)
			break;					//something went wrong
		else if (r == 0)			//pipe closed
		{
			printf("r == 0\n");
			close(writeend);		//close other one
			return 0;
		}							//some letters to capitals

		printf("Data of %d: %s\n", getpid(),buff);

		for (i=0; buff[i]; i++)
			if (rand() > RAND_MAX/2)
				if (buff[i] >= 'a' && buff[i] <= 'z')
					buff[i] -= ('a' - 'A');
									//send back

		if (write(writeend, buff, 1+strlen(buff)) < 0)
			break;
		
		//return 0;
		printf("End of caps: %d\n",getpid());
	}
	printf("Error in %d:\n",getpid() );
	perror("caps");
	return -1;
}