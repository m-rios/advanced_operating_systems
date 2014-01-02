int io(int readend, int writeend1, int writeend2)
{
	int r;
	char buff[SIZE];

	printf("Type lines of text (Ctrl+D to finish):\n");

	for(;;)
	{
		if (fgets(buff,SIZE, stdin)) //Read from keyboard
		{
			if (write(writeend, buff, 1+strlen(buff)) < 0)
				break; 				//if error exit
		}
		else						//if eof close pipe
			close(writeend);

		r = read(readend, buff, SIZE);

		if (r < 0)					//something wrong
			break;
		else if (r == 0)
			return 0; 				//everything ok
	}
									//something has gone wrong
	perror("io");
	return -1;
}