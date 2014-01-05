#include "demux.h"
int demux(int readend1, int readend2, int writeend)
{
	int r1,r2;
	char buff1[SIZE_HALF];
	char buff2[SIZE_HALF];
	char all[SIZE];

	for (;;)
	{
		r1 = read(readend1, buff1, SIZE_HALF);

		if (r1 < 0)
			break;

		r2 = read(readend2, buff2, SIZE_HALF);

		if (r2 < 0)
			break;

		if ((r1 == 0) && (r2 == 0))
		{
			close(writeend);
			return 0;
		}

		printf("Data at demux:\nfrom Tx_B2: %s\nfrom Tx_A : %s\n", buff1, buff2);
		concatenate(all,buff1,buff2);

		if (write(writeend, all, 1+strlen(all)) < 0)
			break;
	}

	perror("demux");
	return -1;
}