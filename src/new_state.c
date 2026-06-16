#include <stdlib.h>

#include "struct_state.h"

int next_id = 0;

State* new_state(void) {
    State* s = malloc(sizeof(State));

    if (s == NULL) {
        return NULL;
    }

    s->id = next_id;
    next_id = next_id + 1;

    s->count = 0;

    return s;
}