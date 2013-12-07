#include "commands.h"

char* mypwd()
{

}
char* myls(char* dir,char arg)
{

}
void mymkdir(char* dir)
{	
	if (mkdir(dir,0775))
		perror(dir);
}
void myrmdir(char* dir)
{

}
void mycd(char* path)
{

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