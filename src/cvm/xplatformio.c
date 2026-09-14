#include "xplatformio.h"

#if CVM_PLATFORM == CVM_PLATFORM_WINDOWS
#include <stdlib.h>
#include <windows.h>
#endif

void cvm_xplatformio_set_title(const char *title) {
#if CVM_PLATFORM == CVM_PLATFORM_WINDOWS
    SetConsoleTitleA(title);
#endif
}

void cvm_xplatformio_execute_command(const char *command) {
#if CVM_PLATFORM == CVM_PLATFORM_WINDOWS
    system(command);
#endif
}

void cvm_xplatformio_set_position(const uint16_t x, const uint16_t y) {
#if CVM_PLATFORM == CVM_PLATFORM_WINDOWS
    COORD coord;
    coord.X = (SHORT)x;
    coord.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif
}
