#include "windows.h"
#include <iostream>
#include <conio.h>
#include <cstdint>
#include <fstream>
#include <string>
#include <sstream>

#define RAM_SIZE (1024 * 1024) // 1KB RAM
#define STACK_SIZE 64
#define USTACK_SIZE 128

#define RELJP(ADDR) if (ADDR > 2147483647) state.pc = state.pc + ADDR - 4294967296; else state.pc = state.pc + ADDR

#define VERSION "CppVM v3.0.0 Indev"


struct VmFlags {
    bool zero = false;
    bool carry = false;
    bool sign = false;
    bool overflow = false;
};

struct VmState {
    bool isRunning = true;

    uint32_t a = 0, b = 0, c = 0; // General purpose registers
    uint32_t na = 0, nb = 0, nc = 0; // Alternative registers TODO consider deprecating?
    uint32_t sp = 0; // Stack Pointer
    uint32_t usp = 0; // User Stack Pointer
    uint32_t pc = 0; // Program Counter

    VmFlags flags = VmFlags();
};

unsigned int ram[RAM_SIZE]; // TODO init ram?
unsigned int stack[STACK_SIZE];
unsigned int ustack[USTACK_SIZE];

auto state = VmState();


std::ifstream fin("bios.cvm"); // Чтение файла


void goto_xy(const SHORT x, const SHORT y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    SetConsoleTitle(VERSION);
    std::cout << "CVM Started" << std::endl; // TODO remove

    while (state.pc < RAM_SIZE - 1) {
        /// erase RAM
        ram[state.pc] = 0;
        state.pc++;
    }
    ram[RAM_SIZE - 1] = 255;
    state.pc = 0;

    std::cout << "Loading bios..." << std::endl; // TODO remove

    int buff, bc = 0;
    if (!fin.is_open()) {
        /// bootloader
        std::cout << "bios.cvm not found" << std::endl;
        system("pause");
        return 0;
    }

    while (bc < RAM_SIZE && !fin.eof()) {
        fin >> buff;
        ram[bc] = buff;
        fin >> buff;
        ram[bc] = ram[bc] * 256 + buff;
        fin >> buff;
        ram[bc] = ram[bc] * 256 + buff;
        fin >> buff;
        ram[bc] = ram[bc] * 256 + buff;
        //std::cout << bc << " " << ram[bc] <<std::endl;
        bc++;
    }
    fin.close();

    std::cout << "CVM is running" << std::endl; // TODO remove
    while (state.isRunning) {
        if (ram[state.pc] == 0) {
            // Do nothing
        } else if (ram[state.pc] == 1) {
            state.a++;
        } else if (ram[state.pc] == 2) {
            state.b++;
        } else if (ram[state.pc] == 3) {
            state.c++;
        } else if (ram[state.pc] == 4) {
            state.a--;
        } else if (ram[state.pc] == 5) {
            state.b--;
        }
        if (ram[state.pc] == 6) {
            state.c--;
        } else if (ram[state.pc] == 7) {
            state.pc++;

            const uint32_t value = ram[state.pc];
            const uint32_t result = state.a - value;

            // Zero: A == value
            state.flags.zero = result == 0;

            // Borrow: A < value, unsigned
            state.flags.carry = state.a < value;

            // Sign: MSB = 1 (negative)
            state.flags.sign = (result & 0x80000000u) != 0;

            // Overflow: occurs when A and B have different
            // signs and the result's sign differs from A.
            state.flags.overflow =
                    ((state.a ^ value) & (state.a ^ result) & 0x80000000u) != 0;
        } else if (ram[state.pc] == 8) {
            const uint32_t result = state.a - state.b;

            // Zero: A == value
            state.flags.zero = result == 0;

            // Borrow: A < value, unsigned
            state.flags.carry = state.a < state.b;

            // Sign: MSB = 1 (negative)
            state.flags.sign = (result & 0x80000000u) != 0;

            // Overflow: occurs when A and B have different
            // signs and the result's sign differs from A.
            state.flags.overflow =
                    ((state.a ^ state.b) & (state.a ^ result) & 0x80000000u) != 0;
        } else if (ram[state.pc] == 9) {
            const uint32_t result = state.a - state.c;

            // Zero: A == value
            state.flags.zero = result == 0;

            // Borrow: A < value, unsigned
            state.flags.carry = state.a < state.c;

            // Sign: MSB = 1 (negative)
            state.flags.sign = (result & 0x80000000u) != 0;

            // Overflow: occurs when A and B have different
            // signs and the result's sign differs from A.
            state.flags.overflow =
                    ((state.a ^ state.c) & (state.a ^ result) & 0x80000000u) != 0;
        } else if (ram[state.pc] == 10) {
            std::cout << state.a;
        } else if (ram[state.pc] == 11) {
            if (state.a > 2147483648U) {
                std::cout << state.a - 4294967296U;
            } else {
                std::cout << state.a;
            }
        } else if (ram[state.pc] == 12) {
            ///unicode?
            if (state.a < 256) {
                char ch;
                ch = (char) state.a;
                //std::cout << ch;
                putchar(ch);
            }
        } else if (ram[state.pc] == 13) {
            putchar('\n');
        } else if (ram[state.pc] == 14) {
            uint32_t readValue;
            std::cin >> readValue;
            state.a = readValue;
        } else if (ram[state.pc] == 15) {
            state.a = getch();
        } else if (ram[state.pc] == 16) {
            system("cls");
        } else if (ram[state.pc] == 17) {
            if (state.sp < STACK_SIZE) {
                stack[state.sp] = state.pc + 1;
                state.sp++;
                state.pc = state.c;
                continue;
            } else {
                std::cout << std::endl << "Error: Stack Overflow" << std::endl;
                state.isRunning = false;
            }
        } else if (ram[state.pc] == 18) {
            uint32_t tempA = state.a;
            uint32_t tempB = state.b;
            uint32_t tempC = state.c;
            state.a = state.na;
            state.b = state.nb;
            state.c = state.nc;
            state.na = tempA;
            state.nb = tempB;
            state.nc = tempC;
        } else if (ram[state.pc] == 19) {
            if (state.sp < STACK_SIZE) {
                stack[state.sp] = state.pc + 2;
                state.sp++;
                state.pc++;
                state.pc = ram[state.pc];
                continue;
            } else {
                std::cout << std::endl << "Error: Stack Overflow" << std::endl;
                state.isRunning = false;
            }
        } else if (ram[state.pc] == 20) {
            state.pc++;
            state.pc = ram[state.pc];
            continue;
        } else if (ram[state.pc] == 21) {
            // equal to
            if (state.flags.zero) {
                state.pc++;
                state.pc = ram[state.pc];
                continue;
            } else {
                state.pc++;
            }
        } else if (ram[state.pc] == 22) {
            // not equal to
            if (!state.flags.zero) {
                state.pc++;
                state.pc = ram[state.pc];
                continue;
            } else {
                state.pc++;
            }
        } else if (ram[state.pc] == 23) {
            // less than
            if (state.flags.carry) {
                state.pc++;
                state.pc = ram[state.pc];
                continue;
            } else {
                state.pc++;
            }
        } else if (ram[state.pc] == 24) {
            // greater than
            if (!state.flags.carry && !state.flags.zero) {
                state.pc++;
                state.pc = ram[state.pc];
                continue;
            } else {
                state.pc++;
            }
        } else if (ram[state.pc] == 25) {
            state.pc = state.c;
            continue;
        } else if (ram[state.pc] == 26) {
            // equal to
            if (state.flags.zero) {
                state.pc = state.c;
                continue;
            }
        } else if (ram[state.pc] == 27) {
            // not equal to
            if (!state.flags.zero) {
                state.pc = state.c;
                continue;
            }
        } else if (ram[state.pc] == 28) {
            // less than
            if (state.flags.carry) {
                state.pc = state.c;
                continue;
            }
        } else if (ram[state.pc] == 29) {
            // greater than
            if (!state.flags.carry && !state.flags.zero) {
                state.pc = state.c;
                continue;
            }
        } else if (ram[state.pc] == 30) {
            state.a = state.b;
        } else if (ram[state.pc] == 31) {
            state.a = state.c;
        } else if (ram[state.pc] == 32) {
            state.b = state.a;
        } else if (ram[state.pc] == 33) {
            state.b = state.c;
        } else if (ram[state.pc] == 34) {
            state.c = state.a;
        } else if (ram[state.pc] == 35) {
            state.c = state.b;
        }
        /// 40-42 free
        else if (ram[state.pc] == 43) {
            state.pc++;
            state.a = ram[state.pc];
        } else if (ram[state.pc] == 44) {
            state.pc++;
            state.b = ram[state.pc];
        } else if (ram[state.pc] == 45) {
            state.pc++;
            state.c = ram[state.pc];
        } else if (ram[state.pc] == 50) {
            state.pc++;
            state.a = ram[ram[state.pc]];
        } else if (ram[state.pc] == 51) {
            state.pc++;
            state.b = ram[ram[state.pc]];
        } else if (ram[state.pc] == 52) {
            state.pc++;
            state.c = ram[ram[state.pc]];
        } else if (ram[state.pc] == 53) {
            state.pc++;
            ram[ram[state.pc]] = state.a;
        } else if (ram[state.pc] == 54) {
            state.pc++;
            ram[ram[state.pc]] = state.b;
        } else if (ram[state.pc] == 55) {
            state.pc++;
            ram[ram[state.pc]] = state.c;
        } else if (ram[state.pc] == 60) {
            state.a = ram[state.a];
        } else if (ram[state.pc] == 61) {
            state.a = ram[state.b];
        } else if (ram[state.pc] == 62) {
            state.a = ram[state.c];
        } else if (ram[state.pc] == 63) {
            state.b = ram[state.a];
        } else if (ram[state.pc] == 64) {
            state.b = ram[state.b];
        } else if (ram[state.pc] == 65) {
            state.b = ram[state.c];
        } else if (ram[state.pc] == 66) {
            state.c = ram[state.a];
        } else if (ram[state.pc] == 67) {
            state.c = ram[state.b];
        } else if (ram[state.pc] == 68) {
            state.c = ram[state.c];
        } else if (ram[state.pc] == 70) {
            ram[state.a] = state.a;
        } else if (ram[state.pc] == 71) {
            ram[state.b] = state.a;
        } else if (ram[state.pc] == 72) {
            ram[state.c] = state.a;
        } else if (ram[state.pc] == 73) {
            ram[state.a] = state.b;
        } else if (ram[state.pc] == 74) {
            ram[state.b] = state.b;
        } else if (ram[state.pc] == 75) {
            ram[state.c] = state.b;
        } else if (ram[state.pc] == 76) {
            ram[state.a] = state.c;
        } else if (ram[state.pc] == 77) {
            ram[state.b] = state.c;
        } else if (ram[state.pc] == 78) {
            ram[state.c] = state.c;
        } else if (ram[state.pc] == 110) {
            state.a = state.a + state.b;
        } else if (ram[state.pc] == 111) {
            state.a = state.a + state.c;
        } else if (ram[state.pc] == 112) {
            state.b = state.b + state.a;
        } else if (ram[state.pc] == 113) {
            state.b = state.b + state.c;
        } else if (ram[state.pc] == 114) {
            state.c = state.c + state.a;
        } else if (ram[state.pc] == 115) {
            state.c = state.c + state.b;
        } else if (ram[state.pc] == 116) {
            state.pc++;
            state.a = state.a + ram[state.pc];
        } else if (ram[state.pc] == 117) {
            state.pc++;
            state.b = state.b + ram[state.pc];
        } else if (ram[state.pc] == 118) {
            state.pc++;
            state.c = state.c + ram[state.pc];
        } else if (ram[state.pc] == 120) {
            state.a = state.a - state.b;
        } else if (ram[state.pc] == 121) {
            state.a = state.a - state.c;
        } else if (ram[state.pc] == 122) {
            state.b = state.b - state.a;
        } else if (ram[state.pc] == 123) {
            state.b = state.b - state.c;
        } else if (ram[state.pc] == 124) {
            state.c = state.c - state.a;
        } else if (ram[state.pc] == 125) {
            state.c = state.c - state.b;
        } else if (ram[state.pc] == 126) {
            state.pc++;
            state.a = state.a - ram[state.pc];
        } else if (ram[state.pc] == 127) {
            state.pc++;
            state.b = state.b - ram[state.pc];
        } else if (ram[state.pc] == 128) {
            state.pc++;
            state.c = state.c - ram[state.pc];
        } else if (ram[state.pc] == 130) {
            state.a = state.a * state.b;
        } else if (ram[state.pc] == 131) {
            state.a = state.a * state.c;
        } else if (ram[state.pc] == 132) {
            state.b = state.b * state.a;
        } else if (ram[state.pc] == 133) {
            state.b = state.b * state.c;
        } else if (ram[state.pc] == 134) {
            state.c = state.c * state.a;
        } else if (ram[state.pc] == 135) {
            state.c = state.c * state.b;
        } else if (ram[state.pc] == 136) {
            state.pc++;
            state.a = state.a * ram[state.pc];
        } else if (ram[state.pc] == 137) {
            state.pc++;
            state.b = state.b * ram[state.pc];
        } else if (ram[state.pc] == 138) {
            state.pc++;
            state.c = state.c * ram[state.pc];
        } else if (ram[state.pc] == 140) {
            state.a = state.a / state.b;
        } else if (ram[state.pc] == 141) {
            state.a = state.a / state.c;
        } else if (ram[state.pc] == 142) {
            state.b = state.b / state.a;
        } else if (ram[state.pc] == 143) {
            state.b = state.b / state.c;
        } else if (ram[state.pc] == 144) {
            state.c = state.c / state.a;
        } else if (ram[state.pc] == 145) {
            state.c = state.c / state.b;
        } else if (ram[state.pc] == 146) {
            state.pc++;
            state.a = state.a / ram[state.pc];
        } else if (ram[state.pc] == 147) {
            state.pc++;
            state.b = state.b / ram[state.pc];
        } else if (ram[state.pc] == 148) {
            state.pc++;
            state.c = state.c / ram[state.pc];
        } else if (ram[state.pc] == 150) {
            state.pc++;
            state.a = state.a & ram[state.pc];
        } else if (ram[state.pc] == 151) {
            state.pc++;
            state.a = state.a | ram[state.pc];
        } else if (ram[state.pc] == 152) {
            state.pc++;
            state.a = state.a ^ ram[state.pc];
        } else if (ram[state.pc] == 153) {
            state.a = ~state.a;
        } else if (ram[state.pc] == 154) {
            state.a = state.a & state.b;
        } else if (ram[state.pc] == 155) {
            state.a = state.a | state.b;
        } else if (ram[state.pc] == 156) {
            state.a = state.a ^ state.b;
        } else if (ram[state.pc] == 160) {
            for (unsigned int &w: ustack) {
                w = 0;
            }
            state.usp = 0;
        } else if (ram[state.pc] == 161) {
            ustack[state.usp] = state.a;
            if (state.usp < USTACK_SIZE) {
                state.usp++;
            }
        } else if (ram[state.pc] == 162) {
            ustack[state.usp] = state.b;
            if (state.usp < USTACK_SIZE) {
                state.usp++;
            }
        } else if (ram[state.pc] == 163) {
            ustack[state.usp] = state.c;
            if (state.usp < USTACK_SIZE) {
                state.usp++;
            }
        } else if (ram[state.pc] == 164) {
            if (state.usp > 0) {
                state.usp--;
                state.a = ustack[state.usp];
            }
        } else if (ram[state.pc] == 165) {
            if (state.usp > 0) {
                state.usp--;
                state.b = ustack[state.usp];
            }
        } else if (ram[state.pc] == 166) {
            if (state.usp > 0) {
                state.usp--;
                state.c = ustack[state.usp];
            }
        } else if (ram[state.pc] == 167) {
            state.pc++;
            ustack[state.usp] = ram[state.pc];
            if (state.usp < USTACK_SIZE) {
                state.usp++;
            }
        } else if (ram[state.pc] == 170) {
            if (kbhit()) {
                state.a = getch();
            }
        } else if (ram[state.pc] == 180) {
            state.pc++;
            if (state.flags.zero) {
                ustack[state.usp] = 1;
            } else {
                ustack[state.usp] = 0;
            }
            if (state.usp < USTACK_SIZE) {
                state.usp++;
            }
            continue;
        } else if (ram[state.pc] == 181) {
            state.pc++;
            if (!state.flags.zero) {
                ustack[state.usp] = 1;
            } else {
                ustack[state.usp] = 0;
            }
            if (state.usp < USTACK_SIZE) {
                state.usp++;
            }
            continue;
        } else if (ram[state.pc] == 182) {
            state.pc++;
            if (state.flags.carry) {
                ustack[state.usp] = 1;
            } else {
                ustack[state.usp] = 0;
            }
            if (state.usp < USTACK_SIZE) {
                state.usp++;
            }
            continue;
        } else if (ram[state.pc] == 183) {
            state.pc++;
            if (!state.flags.carry && !state.flags.zero) {
                ustack[state.usp] = 1;
            } else {
                ustack[state.usp] = 0;
            }
            if (state.usp < USTACK_SIZE) {
                state.usp++;
            }
            continue;
        } else if (ram[state.pc] == 190) {
            state.pc++;
            RELJP(ram[state.pc]);
            continue;
        } else if (ram[state.pc] == 191) {
            if (state.flags.zero) {
                state.pc++;
                RELJP(ram[state.pc]);
                continue;
            } else {
                state.pc = state.pc + 2;
            }
            continue;
        } else if (ram[state.pc] == 192) {
            if (!state.flags.zero) {
                state.pc++;
                RELJP(ram[state.pc]);
                continue;
            } else {
                state.pc = state.pc + 2;
            }
            continue;
        } else if (ram[state.pc] == 193) {
            if (state.flags.carry) {
                state.pc++;
                RELJP(ram[state.pc]);
                continue;
            } else {
                state.pc = state.pc + 2;
            }
            continue;
        } else if (ram[state.pc] == 194) {
            if (!state.flags.carry && !state.flags.zero) {
                state.pc++;
                RELJP(ram[state.pc]);
                continue;
            } else {
                state.pc = state.pc + 2;
            }
            continue;
        } else if (ram[state.pc] == 250) {
            bc = 0;
            uint32_t tmp = 0;
            while (bc < RAM_SIZE) {
                if (ram[bc] != 0) {
                    tmp++;
                }
                bc++;
            }
            std::stringstream mon0;
            std::string mon;
            tmp--;
            std::cout << "RAM Used: " << tmp * 4 << "b / "
                    << RAM_SIZE / 256 << "kb (" << tmp * 100 / RAM_SIZE << "%)"
                    << std::endl << std::endl;
        } else if (ram[state.pc] == 255) {
            if (state.sp == 0) {
                state.isRunning = false;
            } else {
                state.sp--;
                state.pc = stack[state.sp];
                stack[state.sp] = 0;
                continue;
            }
        } else if (ram[state.pc] == 300) {
            char lol[USTACK_SIZE];
            for (int x = 0; x < USTACK_SIZE; x++) {
                lol[x] = static_cast<char>(ustack[x]);
            }
            system(lol);
        } else if (ram[state.pc] == 301) {
            goto_xy(static_cast<SHORT>(state.a), static_cast<SHORT>(state.b));
        }

        state.pc++;
    }
    return 0;
}
