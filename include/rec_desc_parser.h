#ifndef REC_DESC_PARSER_H
#define REC_DESC_PARSER_H

#include <stdbool.h>

#include "struct_nfa.h"

#include "struct_parser.h"

bool parse_expr(Parser* regex, NFA* out_result);

bool parse_term(Parser* regex, NFA* out_result);

bool parse_factor(Parser* regex, NFA* out_result);

bool parse_base(Parser* regex, NFA* out_result);

#endif