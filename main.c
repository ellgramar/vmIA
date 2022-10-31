#include "main.h"


int main(int argc, char *argv[]) {
    FILE *fp = fopen("binfile.bin", "rb");
    struct comp * c = calloc(1, sizeof(struct comp));
    read_machine_code_to_mem(fp, c);
    // print out first 16 uint16_t values of mem
    for (int i = 0; i < 0x20; i++) {
        printf("%d ", c->mem[i]);
    }
    printf("\n");
/*     errno = 1;
    printf("errno: %d\n", errno); */

    return 0;
}