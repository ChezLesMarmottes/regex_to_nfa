#include "struct_nfa.h"
#include "new_state.h"
#include "add_transition.h"

NFA literal(char t) {
    State* s = new_state();
    State* a = new_state();

    add_transition(s, t, a);

    NFA result;
    result.start = s;
    result.accept = a;

    return result;
}