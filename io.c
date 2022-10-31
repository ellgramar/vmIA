#include "io.h"

long size_of_file(FILE *fp) {
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (fsize > 0x8fffffff){
        perror("File is too large, must be less than 4GB or 2G-Shorts");
        return -1;
    }
    return fsize;
}

void read_machine_code_to_mem(FILE *fp, struct comp * computer) {
    long fsize = size_of_file(fp);
    fread(computer->mem, (size_t)fsize, 1, fp);
}

