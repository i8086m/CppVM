#include <conio.h>
#include <stdint.h>
#include <stdio.h>

#include "cvm/config.h"
#include "cvm/fio.h"
#include "cvm/state.h"
#include "cvm/xplatformio.h"

#define RELJP(ADDR) if (ADDR > 2147483647) state.pc = state.pc + ADDR - 4294967296; else state.pc = state.pc + ADDR


unsigned int ram[RAM_SIZE];
unsigned int stack[STACK_SIZE];
unsigned int ustack[USTACK_SIZE];

VmState state;

int main() {
    cvm_xplatformio_set_title(VERSION);

    cvm_state_init(&state);
    cvm_fio_erase(ram, RAM_SIZE);
    cvm_fio_erase(stack, STACK_SIZE);
    cvm_fio_erase(ustack, USTACK_SIZE);
    ram[RAM_SIZE - 1] = 255;

    if (cvm_fio_read_program(ram, "bios.cvm") != 0) {
        printf("Unable to read the program file. Terminating.\n");
        return 1;
    }


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
            printf("%u", state.a);
        } else if (ram[state.pc] == 11) {
            printf("%d", (int32_t) state.a);
        } else if (ram[state.pc] == 12) {
            putchar((char) (state.a & 0xFF));
        } else if (ram[state.pc] == 13) {
            putchar('\n');
        } else if (ram[state.pc] == 14) {
            scanf("%uld", &state.a); // todo. this is unsafe.
        } else if (ram[state.pc] == 15) {
            state.a = getch();
        } else if (ram[state.pc] == 16) {
            cvm_xplatformio_execute_command("cls");
        } else if (ram[state.pc] == 17) {
            if (state.sp < STACK_SIZE) {
                stack[state.sp] = state.pc + 1;
                state.sp++;
                state.pc = state.c;
                continue;
            }
            printf("Error: Stack Overflow\n");
            state.isRunning = false;
        } else if (ram[state.pc] == 19) {
            if (state.sp < STACK_SIZE) {
                stack[state.sp] = state.pc + 2;
                state.sp++;
                state.pc++;
                state.pc = ram[state.pc];
                continue;
            }
            printf("Error: Stack Overflow\n");
            state.isRunning = false;
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
            }
            state.pc++;
        } else if (ram[state.pc] == 22) {
            // not equal to
            if (!state.flags.zero) {
                state.pc++;
                state.pc = ram[state.pc];
                continue;
            }
            state.pc++;
        } else if (ram[state.pc] == 23) {
            // less than
            if (state.flags.carry) {
                state.pc++;
                state.pc = ram[state.pc];
                continue;
            }
            state.pc++;
        } else if (ram[state.pc] == 24) {
            // greater than
            if (!state.flags.carry && !state.flags.zero) {
                state.pc++;
                state.pc = ram[state.pc];
                continue;
            }
            state.pc++;
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
            for (int i = 0; i < USTACK_SIZE; i++) {
                ustack[i] = 0;
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
            }
            state.pc = state.pc + 2;
            continue;
        } else if (ram[state.pc] == 192) {
            if (!state.flags.zero) {
                state.pc++;
                RELJP(ram[state.pc]);
                continue;
            }
            state.pc = state.pc + 2;
            continue;
        } else if (ram[state.pc] == 193) {
            if (state.flags.carry) {
                state.pc++;
                RELJP(ram[state.pc]);
                continue;
            }
            state.pc = state.pc + 2;
            continue;
        } else if (ram[state.pc] == 194) {
            if (!state.flags.carry && !state.flags.zero) {
                state.pc++;
                RELJP(ram[state.pc]);
                continue;
            }
            state.pc = state.pc + 2;
            continue;
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
            char executeBuffer[USTACK_SIZE];
            for (int x = 0; x < USTACK_SIZE; x++) {
                executeBuffer[x] = (char) (ustack[x]);
            }
            cvm_xplatformio_execute_command(executeBuffer);
        } else if (ram[state.pc] == 301) {
            cvm_xplatformio_set_position(state.a, state.b);
        }

        state.pc++;
    }
    return 0;
}
