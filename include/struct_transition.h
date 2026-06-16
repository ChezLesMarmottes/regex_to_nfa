#ifndef STRUCT_TRANSITION_H
#define STRUCT_TRANSITION_H

#include "struct_state.h"

typedef struct {
    char symbol;
    State* target;
} Transition;

#endif