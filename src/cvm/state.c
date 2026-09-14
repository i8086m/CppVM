
#include "state.h"


void cvm_state_init(VmState *state) {
    state->isRunning = true;
    state->a = 0;
    state->b = 0;
    state->c = 0;
    state->sp = 0;
    state->usp = 0;
    state->pc = 0;
    state->flags.zero = 0;
    state->flags.carry = 0;
    state->flags.sign = 0;
    state->flags.overflow = 0;
}