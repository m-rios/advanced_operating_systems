#ifndef DEMUX_H
#define DEMUX_H value

#include "str_hdl.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/param.h>
#include <fcntl.h>

int demux(int readend1, int readend2, int writeend);

#endif

