#include <stdbool.h>

#include "struct_nfa.h"
#include "struct_parser.h"
#include "choose.h"
#include "concat.h"
#include "star.h"
#include "literal.h"

bool parse_expr(Parser* regex, NFA* out_result);
bool parse_term(Parser* regex, NFA* out_result);
bool parse_factor(Parser* regex, NFA* out_result);
bool parse_base(Parser* regex, NFA* out_result);

bool is_literal(char c) {
    return c != '|' &&
           c != '*' &&
           c != '(' &&
           c != ')' &&
           c != '\0';
}

bool parse_expr(Parser* regex, NFA* out_result) {

    NFA left;
    if (!parse_term(regex, &left)) {
        return false;
    }

    while (regex->input[regex->pos] == '|') {
        (regex->pos)++;

        NFA temp, right;

        if(!parse_term(regex, &right)) {
            return false;
        }

        if (!choose(&left, &right, &temp)) {
            return false;
        }

        left = temp;
    }

    *out_result = left;

    return true;
}

bool parse_term(Parser* regex, NFA* out_result) {

    NFA left;
    if (!parse_factor(regex, &left)) {
        return false;
    }

    while (is_literal(regex->input[regex->pos]) || regex->input[regex->pos] == '(') {

        NFA temp, right;

        if(!parse_factor(regex, &right)) {
            return false;
        }

        if (!concat(&left, &right, &temp)) {
            return false;
        }

        left = temp;
    }

    *out_result = left;

    return true;
}

bool parse_factor(Parser* regex, NFA* out_result) {

    NFA left;
    if (!parse_base(regex, &left)) {
        return false;
    }

    while (regex->input[regex->pos] == '*') {
        (regex->pos)++;

        NFA temp;

        if (!star(&left, &temp)) {
            return false;
        }

        left = temp;
    }

    *out_result = left;

    return true;
}

bool parse_base(Parser* regex, NFA* out_result) {
    
    if (regex->input[regex->pos] == '(') {
        (regex->pos)++;

        if (!parse_expr(regex, out_result)) {
            return false;

        }
        if (regex->input[regex->pos] != ')') {
            return false;
        }

        (regex->pos)++;
    }

    else if (is_literal(regex->input[regex->pos])) {
        char c = regex->input[regex->pos];
        (regex->pos)++;

        if (!literal(c, out_result)) {
            return false;
        }
    }

    else {
        return false;
    }

    return true;
}