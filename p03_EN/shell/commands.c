#include "commands.h"

void mypwd(char* path)
{
	//getcwd(path, sizeof(path));
	//	perror(path);
}
char* myls(char* dir,char* arg)
{
	char* _ls = "";
	char* _wd = NULL;
	DIR* _dirp;
	struct dirent* _entry;

	if (dir == NULL)
	{
		//_wd = current directory
	}else
		_wd = dir;

	if ((_dirp = opendir(_wd)) == NULL) //something goes wrong
		perror(_wd);

	if (arg == NULL)
	{
		while((_entry = readdir(_dirp)) != NULL)
		{
			if (_entry->d_name[0] != '.')
			{
				//add somehow d_name to _ls
			}
		}
	}
	else if (strcmp(arg,"-l") == 0) //detailed mode
	{
		while((_entry = readdir(_dirp)) != NULL)
		{
			//do something
		}
	}
	else
		printf("Argument unknown: %s\n",arg );
	

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
char* mycat(char* dir)
{

}
void mycp(char* source, char* origin)
{

}
void myrm(char* file)
{

}