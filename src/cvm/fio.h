
#pragma once

#include <stdint.h>

void cvm_fio_erase(uint32_t *region, uint32_t size);

int cvm_fio_read_program(uint32_t *memory, const char *filename);
