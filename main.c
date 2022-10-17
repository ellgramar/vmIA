#include "main.h"

int main(int argc, char *argv[]) {
    FILE *fp = fopen("binfile.bin", "rb");
    read_file_to_mem(fp, mem);
    // print out first 16 uint16_t values of mem
    for (int i = 0; i < 20; i++) {
        printf("%d ", mem[i]);
    }
    printf("\n");

    return 0;
}