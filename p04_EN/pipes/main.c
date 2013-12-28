int main()
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
		case 0: 	close(forth[1]);	//child
					close(back[0]);
					return io(forth[0], back[1]);
		default: 	close(forth[0]);
					close(back[1]);
					r = caps(back[0],forth[1]);
					wait(NULL);
					return r;
	}
}