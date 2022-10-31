/*This file handles loading and storing the memoryspace*/

#ifndef IO_C
#define IO_C

#include <stdio.h>
#include <stdint.h>

#include "comp.h"

// functions
long size_of_file(FILE *fp);    // returns the size of a file in bytes
void read_machine_code_to_mem(FILE *fp, struct comp * computer);    // reads a file into memory

#endif