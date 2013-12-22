#include "commands.h"

char* mypwd()
{
	char* _return = (char*) malloc(MAXPATHLEN);
	getcwd(_return,MAXPATHLEN);
	return _return;
}

void myls(char* dir,int _d_mod)
{
	char* _wd;
	DIR* _dirp;
	struct dirent* _entry;

	if (dir == NULL)
		_wd = mypwd();
	else
		_wd = dir;

	if ((_dirp = opendir(_wd)) == NULL) //something goes wrong
	{	
		perror(_wd);
		return;
	}
	if (_d_mod) //detailed mode
	{
		struct stat _fileStat;
		char* path = (char*) malloc(MAXPATHLEN); 
		while((_entry = readdir(_dirp)) != NULL)
		{
			strcpy(path,_wd);
			strcat(path,"/");
			strcat(path,_entry->d_name);
			stat(path,&_fileStat);
			printf("%us %s %s %10lld %s\n",
				_fileStat.st_mode,getpwuid(_fileStat.st_uid)->pw_name,
				getgrgid(_fileStat.st_gid)->gr_name,(long long)_fileStat.st_size,
				_entry->d_name);
		}
	}
	else //simple mode
		while((_entry = readdir(_dirp)) != NULL)
			printf("%s\n",_entry->d_name);

	if (dir == NULL)
		free(_wd);

	if (closedir(_dirp) != 0) //something goes wrong
		perror("error when closing directory");
}
void mymkdir(char* dir)
{	
	if (mkdir(dir,0775))
		perror(dir);
}
void myrmdir(char* dir)
{
	if (rmdir(dir))
		perror(dir);
}
void mycd(char* path)
{
	if (chdir(path))
		perror(path);
}
void mycat(char* _path)
{
	//open file
	int _fd = open(_path,O_RDONLY);
	if (_fd == -1)
	{
		perror(_path);
		return;
	}

	//test if is a regular file
	struct stat _sbuff;
	fstat(_fd,&_sbuff);
	if (S_ISREG(_sbuff.st_mode)==0)
	{
		printf("error: path is not a regular file\n");
		return;
	}	

	//size of the file to read
	char* _file = "";
	off_t _fileSize = lseek(_fd,0,SEEK_END);
	off_t _offset = lseek(_fd,0,SEEK_SET);
	long _pageSize = sysconf(_SC_PAGE_SIZE);
	printf("size: %lld\n",_fileSize );
	while(_offset<_fileSize)
	{
		_file = (char*) mmap(NULL,_pageSize,PROT_READ,MAP_SHARED,_fd,_offset);
		printf("%s", _file);		
		munmap(_file,_pageSize);
		_offset = lseek(_fd,_pageSize,SEEK_CUR);
	}

	if (close(_fd)!=0)
		perror("Problem closing file");

}
void mycp(char* _source, char* _dest)
{
	//create new file
	int _destFd = open(_dest,O_CREAT|O_WRONLY,0644);
	if (_destFd == -1)
	{
		perror(_dest);
		return;
	}
	//open source file
	int _sourceFd = open(_source,O_RDONLY);
	if (_sourceFd == -1)
	{
		perror(_source);
		return;
	}
	struct stat _sbuff;
	fstat(_sourceFd,&_sbuff);
	if (S_ISREG(_sbuff.st_mode)==0)
	{	
		printf("error: path is not a file\n");
		return ;
	}
	//copy	
	char _buffer[MAXREAD];
	size_t _rSize;
	while((_rSize = read(_sourceFd,_buffer,sizeof(_buffer))) > 0)
		write(_destFd,_buffer,_rSize);

	if (close(_sourceFd) != 0)
		perror(_source);
	if (close(_destFd) != 0)
		perror(_dest);
}
void myrm(char* file)
{
	if (unlink(file) == -1)
		perror(file);
}