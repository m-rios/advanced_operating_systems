#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/param.h>
#include <pwd.h>
#include "grp.h"

#define MAXREAD 512
char* mypwd();
void myls(char* dir,int _d_mod);
void mymkdir(char* dir);
void myrmdir(char* dir);
void mycd(char* path);
void mycat(char* _path);
void mycp(char* source, char* _dest);
void myrm(char* file);

#endif