#ifndef CONCAT_H
#define CONCAT_H

#include <stdbool.h>

#include "struct_nfa.h"

bool concat(NFA* a, NFA* b, NFA* out_result);

#endif