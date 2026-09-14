
#pragma once

#include <stdint.h>


#define CVM_PLATFORM_GENERIC 0
#define CVM_PLATFORM_WINDOWS 1
#define CVM_PLATFORM_LINUX   2

#if defined(_WIN32)
    #define CVM_PLATFORM CVM_PLATFORM_WINDOWS
#elif defined(__linux__)
    #define CVM_PLATFORM CVM_PLATFORM_LINUX
#else
    #define CVM_PLATFORM CVM_PLATFORM_GENERIC
#endif


void cvm_xplatformio_set_title(const char *title);
void cvm_xplatformio_execute_command(const char *command);
void cvm_xplatformio_set_position(uint16_t x, uint16_t y);

