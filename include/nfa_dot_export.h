#ifndef NFA_DOT_EXPORT_H
#define NFA_DOT_EXPORT_H

#include <stdio.h>
#include <stdbool.h>

#include "struct_nfa.h"

bool write_nfa_dot(FILE *out, const NFA *nfa);
bool export_nfa_dot(const NFA *nfa, const char *filename);

#endif