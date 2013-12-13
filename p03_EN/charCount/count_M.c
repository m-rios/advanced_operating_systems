#include "count_M.h"

int countCharacters(int _fd, char _character)
{
	/* calculates using memory mapping the number of occurrences of the
	specified character in the file*/
	int _nChar = 0;
	int _fileSize = lseek(_fd,0,SEEK_END);
	char* _file = (char*) mmap(NULL,_fileSize,PROT_READ,MAP_PRIVATE,_fd,0);
	//look for char concurrences
	int i;
	for (i = 0; i < _fileSize; ++i)
	{
		if (_file[i] == _character)
			_nChar++;
	}
	//free memory
	munmap(&_file,_fileSize);
	return _nChar;
}