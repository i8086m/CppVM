#include "fio.h"

#include <stdio.h>
#include "config.h"


void cvm_fio_erase(uint32_t *region, const uint32_t size) {
    // Erase a memory region (ram, stack, etc.)
    for (int i = 0; i < size - 1; i++) {
        region[i] = 0;
    }
}

int cvm_fio_read_program(uint32_t *memory, const char *filename) {
    FILE *fin = fopen(filename, "r");

    if (fin == NULL) {
        return -1;
    }

    for (int w = 0; w < RAM_SIZE; w++) {
        uint32_t value = 0;

        for (int b = 0; b < 4; b++) {
            unsigned int byte = 0;
            const int code = fscanf(fin, "%u", &byte);

            if (code == EOF) {
                fclose(fin);
                return 0;
            }

            if (code != 1 || byte > 255) {
                fclose(fin);
                return -2;
            }

            value = (value << 8) | byte;
        }

        memory[w] = value;
    }


    return -3;
}
