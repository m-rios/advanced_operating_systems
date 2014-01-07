#include "main.h"
#include "cap_trans.h"
#include "demux.h"
#include "io_mux.h"

int main()
{
	int capsB1[2], capsB2[2], capsA[2], back[2], demuxA[2], demuxB[2], r;
	if (pipe(capsB1) || pipe(capsB2) || pipe(capsA) ||
		pipe(back) || pipe(demuxA) || pipe(demuxB) )
	{
		perror("creating pipe");
		return -1;
	}

	int pid;

	if (fork() == 0) //IOdemux process
	{
		close(back[1]);
		close(capsA[0]);
		close(capsB1[0]);
		return io(back[0], capsB1[1], capsA[1]);
	}

	//back to parent
	if (fork() == 0) //Tx_B1
	{
		printf("Tx_B1 %d\n", getpid());
		close(capsB1[1]);
		close(capsB2[0]);
		r = caps(capsB1[0], capsB2[1]);
		printf("POLLA\n");
		return r;
	}

	if (fork() == 0)//Tx_B2
	{
		printf("Tx_B2 %d\n", getpid());
		close(demuxB[0]);
		close(capsB2[1]);
		return caps(capsB2[0],demuxB[1]);
	}

	if (fork() == 0) //Tx_A
	{
		printf("Tx_A %d\n", getpid());
		close(capsA[1]);
		close(demuxA[0]);
		return caps(capsA[0], demuxA[1]);
	}

	//wait(NULL);
	printf("RABO\n");
	//wait(NULL);
	printf("VERGA\n");

	close(demuxB[1]);
	close(demuxA[1]);
	close(back[0]);
	r = demux(demuxB[0], demuxA[0], back[1]);

	//wait(NULL);
	printf("Me vas a comer toda la PULA TAL CUAL\n");

	return 0;
}