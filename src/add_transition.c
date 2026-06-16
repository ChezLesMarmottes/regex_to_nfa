#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "struct_state.h"

bool add_transition(State* from, char symbol, State* to) {
    if (from == NULL || to == NULL || from->count >= MAX_TRANSITIONS) {
        return false;
    }

    Transition T;
    T.symbol = symbol;
    T.target = to;
    
    from->transitions[from->count] = T;
    from->count += 1;
    return true;
}