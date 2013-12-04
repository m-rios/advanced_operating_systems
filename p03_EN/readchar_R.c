char readCharacter (int _fd, int _position)
{
	/*returns without using memory mapping the character stored in the
	indicated position of the file whose descriptor is passed*/
	char _return;
	off_t _off = lseek(_fd,_position,SEEK_SET);
	pread(_fd,&_return,sizeof(char),_off);
	return _return;
}