int main() //original main
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
	else if (pid = 0) //I/O process
	{
		//call i/o
	}
	else if ((pid = fork()) == -1)
	{
		perror("fork Tx_B1");
		return -2;
	}
	else if (pid == 0) //Tx_B1;
	{
		int pidaux, ret;
		if ((pidaux = fork()) == -1)
		{
			perror("fork Tx_B2");
			return -2;
		}
		else if (pidaux = 0) //Tx_B2
		{
			
		}
		//call caps
		wait(NULL); //wait for Tx_B2
		return ret;
	}else if ((pid = fork()) == -1)
	{
		perror("fork Tx_A");
		return -2;
	}else if (pid == 0)
	{
		//call caps
	}
	wait(NULL);		//wait for both
	wait(NULL);		//Tx_A & Tx_B1
	//call demux proc
	wait(NULL); //wait for I/O

}