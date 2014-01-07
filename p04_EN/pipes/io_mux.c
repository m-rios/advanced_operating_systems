#include "io_mux.h"
int io(int readend, int writeend1, int writeend2)
{
	int r;
	char buff[SIZE], half1[SIZE_HALF], half2[SIZE_HALF];

	printf("Type lines of text (Ctrl+D to finish):\n");

	for(;;)
	{
		if (fgets(buff,SIZE, stdin)) //Read from keyboard
		{
			split(buff,half1,half2);

			if ((write(writeend1, half1, 1+strlen(half1)) < 0)
				|| (write(writeend2, half2, 1+strlen(half2)) < 0))
				break; 				//if error exit
		}
		else						//if eof close pipe
		{	
			printf("io: EOF\n");
			close(writeend1);
			close(writeend2);
		}
		printf("LEYENDO\n");
		r = read(readend, buff, SIZE);
		printf("YA HE LEIDO LOCO: %s\n",buff);

		if (r < 0)					//something wrong
			break;
		else if (r == 0)			//pipe closed
		{
			printf("io: r == 0\n");
			close(readend);			//close other end
			return 0;
		}
		fputs(buff, stdout);
	}
									//something has gone wrong
	perror("io");
	return -1;
}