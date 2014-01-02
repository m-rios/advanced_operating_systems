#include "main.h"
/*int main() //original main
{
	int forth[2], back[2], r;

	if (pipe((forth)) || pipe(back))
	{
		perror("pipe");
		return -1;
	}

	switch(fork())
	{
		case -1: 	perror("fork");  	//error
					return -2;
		case 0: 	close(forth[1]);	//IO mux process (child)
					close(back[0]);
					return io(forth[0], back[1]);
		default: 	close(forth[0]);	//main process
					close(back[1]);
					r = caps(back[0],forth[1]);
					wait(NULL);
					return r;
	}
}
*/
int main() //my main
{
	int pipe1[2], pipe2[2], pipe3[2], pipe4[2], pipe5[2], pipe6[2], r, pid;

	if (pipe(pipe1) || pipe(pipe2) || pipe(pipe2) ||
		pipe(pipe4) || pipe(pipe5) || pipe(pipe6) )
	{
		perror("pipe");
		return -1;
	}

	if ((pid = fork()) == -1)
	{
		perror("fork I/O");
		return -2;
	}
	else if (pid == 0) //I/O process
	{
		printf("I/O\n");
		sleep(2);
		return 0;
	}
	else if ((pid = fork()) == -1)
	{
		perror("fork Tx_B1");
		return -2;
	}
	else if (pid == 0) //Tx_B1;
	{
		int pidaux, ret;
		printf("Tx_B1\n");
		if ((pidaux = fork()) == -1)
		{
			perror("fork Tx_B2");
			return -2;
		}
		else if (pidaux == 0) //Tx_B2
		{
			printf("Tx_B2\n");
			caps(pipe3[0], pipe5[1]);
			return 0;
		}
		caps(pipe1[0], pipe3[1]);
		wait(NULL); //wait for Tx_B2
		return ret;
	}else if ((pid = fork()) == -1)
	{
		perror("fork Tx_A");
		return -2;
	}else if (pid == 0)
	{
		//call caps
		caps(pipe2[0], pipe4[1]);
		printf("Tx_A\n");
		return 0;
	}
	wait(NULL);		//wait for both
	wait(NULL);		//Tx_A & Tx_B1
	printf("demux\n");
	//call demux proc
	if (demux(pipe5[0], pipe4[0], pipe6[1]) < 0)
		return -1;
	wait(NULL); //wait for I/O
	printf("io kill\n");

}