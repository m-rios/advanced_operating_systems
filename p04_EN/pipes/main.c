#include "main.h"
#include "cap_trans.h"
#include "demux.h"
#include "io_mux.h"
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
		printf("I/O: %d\n", getpid());
		close(pipe6[1]);
		close(pipe1[0]);
		close(pipe2[0]);
		return io(pipe6[0], pipe1[1], pipe2[1]);
	}
	else if ((pid = fork()) == -1)
	{
		perror("fork Tx_B1");
		return -2;
	}
	else if (pid == 0) //Tx_B1;
	{
		
		int pidaux, ret;
		printf("Tx_B1: %d\n", getpid());
		if ((pidaux = fork()) == -1)
		{
			perror("fork Tx_B2");
			return -2;
		}
		else if (pidaux == 0) //Tx_B2
		{
			//close(pipe3[1]);
			close(pipe5[0]);
			printf("Tx_B2: %d\n", getpid());
			caps(pipe3[0], pipe5[1]);
			return 0;
		}
		//close(pipe1[1]);
		//close(pipe3[0]);
		ret = caps(pipe1[0], pipe3[1]);
		//close(pipe1[0]);
		//close(pipe3[1]);
		wait(NULL); //wait for Tx_B2
		return ret;
	}else if ((pid = fork()) == -1)
	{
		perror("fork Tx_A");
		return -2;
	}else if (pid == 0)
	{
		//call caps
		//close(pipe2[1]); close(pipe4[0]);
		printf("Tx_A: %d\n", getpid());		
		return caps(pipe2[0], pipe4[1]);
	}

	wait(NULL);		//wait for both
	wait(NULL);		//Tx_A & Tx_B1
	printf("demux\n");
	//call demux proc
	if (demux(pipe5[0], pipe4[0], pipe6[1]) < 0)
		return -1;
	wait(NULL); //wait for I/O
	printf("io kill\n");
	return 0;
}