#include "main.h"

int main()
{
	int capsB1[2], capsB2[2], capsA[2], back[2], demuxA[2], demuxB[2], pid;
	if (pipe(capsB1) || pipe(capsB2) || pipe(capsA) ||
		pipe(back) || pipe(demuxA) || pipe(demuxB) )
	{
		perror("creating pipe");
		return -1;
	}

	if ((pid = fork()) == 0) //IOdemux process
	{
		close(back[1]);
		close(capsB2[1]);
		close(demuxB[1]);
		close(demuxA[1]);
		return io(back[0], capsB1[1], capsA[1]);
	}
	else if (pid == -1)
	{
		perror("fork");
		return -2;
	}

	close(back[0]);
	close(capsB1[1]);
	close(capsA[1]);

	//back to parent
	if ((pid = fork()) == 0) //Tx_B1
	{
		return caps(capsB1[0], capsB2[1]);
	}
	else if (pid == -1)
	{
		perror("fork");
		return -2;
	}

	close(capsB1[0]);
	close(capsB2[1]);

	if ((pid = fork()) == 0)//Tx_B2
	{
		return caps(capsB2[0],demuxB[1]);
	}
	else if (pid == -1)
	{
		perror("fork");
		return -2;
	}

	close(capsB2[0]);
	close(demuxB[1]);

	if ((pid = fork()) == 0) //Tx_A
	{
		return caps(capsA[0], demuxA[1]);
	}
	else if (pid == -1)
	{
		perror("fork");
		return -2;
	}
	close(capsA[0]);
	close(demuxA[1]);

	return demux(demuxB[0], demuxA[0], back[1]);
}