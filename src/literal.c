#include <stdbool.h>
#include <stdlib.h>

#include "struct_nfa.h"
#include "new_state.h"
#include "add_transition.h"

bool literal(char transition, NFA* out_result) {
    if (out_result == NULL) {
        return false;
    }

    State* start = new_state();
    State* accept = new_state();

    if (start == NULL || accept == NULL) goto fail;

    if (!add_transition(start, transition, accept)) goto fail;

    out_result->start = start;
    out_result->accept = accept;

    return true;

fail:
    free(start);
    free(accept);
    return false;
}