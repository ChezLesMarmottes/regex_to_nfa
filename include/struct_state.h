#ifndef STRUCT_STATE_H
#define STRUCT_STATE_H

#include "struct_transition.h"

#define MAX_TRANSITIONS 64

typedef struct State {
    int id;
    int count;
    Transition transitions[MAX_TRANSITIONS];
} State;

#endif