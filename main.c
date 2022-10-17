/* #include "main.h" */

// includes
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//  needed for i/o and file support
#include <sys/termios.h>
#include <unistd.h>
#include <sys/stat.h>

//  structures
uint16_t mem[0x8fffffff];

int main(int argc, char *argv[]) {
    long len = 0;
     // check if argc < 2
    if (argc < 2){
        for (long int i = 0; i <= 0x8fffffff; i++){
            mem[i] = 0;
        }
    }
    else {
        // open file
        FILE *fp = fopen(argv[1], "r");
        // get size of file
        fseek(fp, 0L, SEEK_END);
        long size = ftell(fp);
        // reset stream
        rewind(fp);
        char * buffer = malloc(size + 1);
        char c = 0;
        long counter = 0, len = size;
        while ((c = fgetc(fp)) != EOF){
            buffer[counter] = c;
            counter++;
        }
        for (int i = 0; i < size; i++){
            mem[i] = (uint16_t)((0x100 * buffer[i]) + buffer[i + 1]);
            ++i;
        }
    }
    uint16_t tire = 0x41 ;
    uint16_t tires = 0b1000001;
    int counter = 0;
    while (mem[counter] < len){
        printf(" %d\n", mem[counter]);
        counter++;
    }

    return 0;
}