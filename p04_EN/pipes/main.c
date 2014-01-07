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

	if (fork() == 0) //IOdemux process
	{
		close(back[1]);
		close(capsA[0]);
		close(capsB1[0]);
		close(capsB2[0]); close(capsB2[1]);
		close(demuxB[0]); close(demuxB[1]);
		close(demuxA[0]); close(demuxA[1]);
		return io(back[0], capsB1[1], capsA[1]);
	}

	//back to parent
	if (fork() == 0) //Tx_B1
	{
		close(capsB1[1]);
		close(capsB2[0]);
		close(capsA[0]); close(capsA[1]);
		close(back[0]); close(back[1]);
		close(demuxA[0]); close(demuxA[1]);
		close(demuxB[0]); close(demuxB[1]);
		r = caps(capsB1[0], capsB2[1]);
		return r;
	}
	close(capsB1[1]);
	close(capsA[1]);
	close(back[0]);

	if (fork() == 0)//Tx_B2
	{
		close(demuxB[0]);
		close(capsB2[1]);
		close(capsA[0]); close(capsA[1]);
		close(capsB1[0]); close(capsB1[1]);
		close(back[0]); close(back[1]);
		close(demuxA[0]); close(demuxA[1]);
		return caps(capsB2[0],demuxB[1]);
	}
	close(capsB1[0]);
	close(capsB2[1]);
	close(demuxB[1]);

	if (fork() == 0) //Tx_A
	{
		close(capsB1[0]); close(capsB1[1]);
		close(capsB2[0]); close(capsB2[1]);
		close(back[0]); close(back[1]);
		close(demuxB[0]); close(demuxB[1]);
		close(capsA[1]);
		close(demuxA[0]);
		return caps(capsA[0], demuxA[1]);
	}
	close(capsA[0]);
	close(demuxA[1]);


	r = demux(demuxB[0], demuxA[0], back[1]);

	//wait(NULL);
	//wait(NULL);
	wait(NULL);
	wait(NULL);


	return 0;
}