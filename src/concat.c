#include <stdlib.h>
#include <stdbool.h>

#include "struct_nfa.h"
#include "add_transition.h"
#include "constants.h"

bool concat(NFA* a, NFA* b, NFA* out_result) {
    if (a == NULL || b == NULL || out_result == NULL) return false;

    if (a->start == NULL || a->accept == NULL || b->start == NULL || b->accept == NULL) return false;

    if (!add_transition(a->accept, EPSILON, b->start)) return false;

    out_result->start = a->start;
    out_result->accept = b->accept;

    return true;
}