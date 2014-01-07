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
			close(writeend1);
			close(writeend2);
		}
		r = read(readend, buff, SIZE);

		if (r < 0)					//something wrong
			break;
		else if (r == 0)			//pipe closed
		{
			close(readend);			//close other end
			return 0;
		}
		fputs(buff, stdout);
	}
									//something has gone wrong
	perror("io");
	return -1;
}

int main(int argc, char const *argv[])
{
	if (argc < 3 || argc > 4)
	{
		printf("wrong number of parameters\n");
		return -1;
	}

	const char* input = argv[1];
	const char* outputA = argv[2];
	const char* outputB = argv[3];

	int FoutA = open(outputA, O_WRONLY);
	int FoutB = open(outputB, O_WRONLY);
	int Fin = open(input, O_RDONLY);

	if (FoutA == -1 || FoutB == -1 || Fin == -1)
	{
		perror("pipe doesn't exist");
		return -1;
	}

	return io(Fin, FoutA, FoutB);
}