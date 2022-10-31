/* This is the file that actually runs the computer.
it is  involved in setting up the memory space,
and running the program

The goal is to remove as much std includes from this file as possible*/

#ifndef MAIN_H
#define MAIN_H

// includes
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//  needed for i/o support
#include <sys/termios.h>
#include <unistd.h>
// project includes
#include "io.h"


extern int errno;

#endif