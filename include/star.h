#ifndef STAR_H
#define STAR_H

#include <stdbool.h>

#include "struct_nfa.h"

bool star(NFA* a, NFA* out_result);

#endif