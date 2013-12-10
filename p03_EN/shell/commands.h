#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>


void mypwd(char* path);
char* myls(char* dir,char* arg);
void mymkdir(char* dir);
void myrmdir(char* dir);
void mycd(char* path);
char* mycat(char* dir);
void mycp(char* source, char* origin);
void myrm(char* file);
void exit(); //maybe a function is not needed

#endif