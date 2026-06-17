#ifndef ALTERNATE_H
#define ALTERNATE_H

#include <stdbool.h>

#include "struct_nfa.h"

bool alternate(NFA* a, NFA* b, NFA* out_result);

#endif