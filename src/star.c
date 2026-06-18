#include <stdlib.h>
#include <stdbool.h>

#include "struct_nfa.h"
#include "add_transition.h"
#include "constants.h"
#include "new_state.h"

bool star(NFA* a, NFA* out_result) {
    if (a == NULL || out_result == NULL) {
        return false;
    }

    if (a->start == NULL || a->accept == NULL) {
        return false;
    }

    State* start = new_state();
    State* accept = new_state();

    if (start == NULL || accept == NULL) goto fail;

    if (!add_transition(start, EPSILON, a->start)) goto fail;
    if (!add_transition(start, EPSILON, accept)) goto fail;
    if (!add_transition(a->accept, EPSILON, a->start)) goto fail;
    if (!add_transition(a->accept, EPSILON, accept)) goto fail;

    out_result->start = start;
    out_result->accept = accept;
    return true;

fail:
    free(start);
    free(accept);
    return false;
}