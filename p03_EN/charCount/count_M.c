#include "count_M.h"

int countCharacters(int _fd, char _character)
{
	/* calculates using memory mapping the number of occurrences of the
	specified character in the file*/
	int _nChar = 0;
	char* _file = (char*) mmap(NULL,MAX_SIZE,PROT_READ,MAP_PRIVATE,_fd,0);
	//look for char concurrences
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		if (_file[i] == _character)
			_nChar++;
	}
	//free memory
	munmap(&_file,MAX_SIZE);
	return _nChar;
}