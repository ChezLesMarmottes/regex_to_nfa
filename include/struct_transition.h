#ifndef STRUCT_TRANSITION_H
#define STRUCT_TRANSITION_H

typedef struct State State;

typedef struct Transition {
    char symbol;
    State* target;
} Transition;

#endif