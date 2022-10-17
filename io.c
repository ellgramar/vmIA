#include "io.h"

long size_of_file(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return fsize;
}

void read_file_to_mem(FILE *fp, uint16_t *mem) {
    long fsize = size_of_file(fp);
    fread(mem, fsize, 1, fp);
}