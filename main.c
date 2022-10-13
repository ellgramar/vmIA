/* #include "main.h" */

// includes
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//  needed for i/o support
#include <sys/termios.h>
#include <unistd.h>

//  structures
uint16_t mem[0xffffffff];

int main(int argc, char *argv[]) {
    // check if argc < 2
    if (argc < 2){
        for (long int i = 0; i <= 0xffffffff; i++){
            mem[i] = 0;
        }
    }
    else {
        // open file
        FILE *fp = fopen(argv[1], "r");
        // get size of fp
        fseek(fp, 0L, SEEK_END);
        int size = ftell(fp);
        // reset fp
        fseek(fp, 0L, SEEK_SET);
        // read file into mem
        fread(mem, size, 1, fp);
    }
    printf("%d", mem[0]);
    int counter = 1;
    while (mem[counter] != 0){
        printf(" %d", mem[counter]);
        counter++;
    }
    return 0;
}