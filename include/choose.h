#ifndef CHOOSE_H
#define CHOOSE_H

#include <stdbool.h>

#include "struct_nfa.h"

bool choose(NFA* a, NFA* b, NFA* out_result);

#endif