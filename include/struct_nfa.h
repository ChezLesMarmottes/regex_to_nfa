#ifndef STRUCT_NFA_H
#define STRUCT_NFA_H

#include "struct_state.h"

typedef struct {
    State* start;
    State* accept;
} NFA;

#endif