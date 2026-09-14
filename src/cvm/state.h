
#pragma once
#include <stdint.h>

struct VmFlags {
    bool zero;
    bool carry;
    bool sign;
    bool overflow;
} typedef VmFlags;


struct VmState {
    bool isRunning;

    uint32_t a, b, c; // General purpose registers
    uint32_t sp; // Stack Pointer
    uint32_t usp; // User Stack Pointer
    uint32_t pc; // Program Counter

    VmFlags flags;
} typedef VmState;



void cvm_state_init(VmState *state);