#include "cap_trans.h"
int caps(int readend, int writeend)
{
	int i, r;
	char buff[SIZE];

	srand((unsigned)getpid() ^ (unsigned) time(NULL));

	for(;;)
	{
		r = read(readend, buff, SIZE);


		if (r< 0)
			break;					//something went wrong
		else if (r == 0)			//pipe closed
		{
			close(writeend);		//close other one
			return 0;
		}							//some letters to capitals

		for (i=0; buff[i]; i++)
			if (rand() > RAND_MAX/2)
				if (buff[i] >= 'a' && buff[i] <= 'z')
					buff[i] -= ('a' - 'A');
									//send back

		if (write(writeend, buff, 1+strlen(buff)) < 0)
			break;
		
		//return 0;
	}
	perror("caps");
	return -1;
}

int main(int argc, char const *argv[])
{
	if (argc < 2 || argc > 3)
	{
		printf("wrong number of parameters\n");
		return -1;
	}

	const char* input = argv[1];
	const char* output = argv[2];

	int Fin = open(input, O_RDONLY);
	int Fout = open(output, O_WRONLY);

	if (Fin == -1 || Fout == -1)
	{
		perror("pipe doesn't exist");
		return -1;
	}

	return caps(Fin, Fout);
}