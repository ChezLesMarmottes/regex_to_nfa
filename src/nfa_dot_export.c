// nfa_dot_export.c

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "struct_state.h"
#include "struct_nfa.h"
#include "constants.h"

typedef struct {
    const State **items;
    size_t count;
    size_t cap;
} VisitedSet;

static void visited_free(VisitedSet *set) {
    if (set == NULL) {
        return;
    }
    free(set->items);
    set->items = NULL;
    set->count = 0;
    set->cap = 0;
}

static bool visited_contains(const VisitedSet *set, const State *s) {
    if (set == NULL || s == NULL) {
        return false;
    }

    for (size_t i = 0; i < set->count; ++i) {
        if (set->items[i] == s) {
            return true;
        }
    }
    return false;
}

static bool visited_add(VisitedSet *set, const State *s) {
    if (set == NULL || s == NULL) {
        return false;
    }

    if (set->count == set->cap) {
        size_t new_cap = (set->cap == 0) ? 16 : (set->cap * 2);
        const State **new_items = realloc(set->items, new_cap * sizeof(*new_items));
        if (new_items == NULL) {
            return false;
        }
        set->items = new_items;
        set->cap = new_cap;
    }

    set->items[set->count++] = s;
    return true;
}

static const char *symbol_label(char symbol, char *buf, size_t buf_size) {
    if (symbol == EPSILON) {
        return "ε";
    }

    unsigned char c = (unsigned char)symbol;

    if (c == '\\' || c == '"') {
        if (buf_size >= 3) {
            buf[0] = '\\';
            buf[1] = (char)c;
            buf[2] = '\0';
            return buf;
        }
    }

    if (isprint(c)) {
        if (buf_size >= 2) {
            buf[0] = (char)c;
            buf[1] = '\0';
            return buf;
        }
    }

    if (buf_size >= 6) {
        snprintf(buf, buf_size, "0x%02X", c);
        return buf;
    }

    return "?";
}

static bool emit_state_recursive(FILE *out, const State *state, const State *accept, VisitedSet *visited) {
    if (out == NULL || state == NULL || visited == NULL) {
        return false;
    }

    if (visited_contains(visited, state)) {
        return true;
    }

    if (!visited_add(visited, state)) {
        return false;
    }

    fprintf(out,
            "    q%d [label=\"q%d\", shape=%s];\n",
            state->id,
            state->id,
            (state == accept) ? "doublecircle" : "circle");

    for (int i = 0; i < state->count; ++i) {
        const Transition *tr = &state->transitions[i];
        if (tr->target == NULL) {
            return false;
        }

        char label_buf[32];
        const char *label = symbol_label(tr->symbol, label_buf, sizeof(label_buf));

        fprintf(out,
                "    q%d -> q%d [label=\"%s\"];\n",
                state->id,
                tr->target->id,
                label);

        if (!emit_state_recursive(out, tr->target, accept, visited)) {
            return false;
        }
    }

    return true;
}

bool write_nfa_dot(FILE *out, const NFA *nfa) {
    if (out == NULL || nfa == NULL || nfa->start == NULL || nfa->accept == NULL) {
        return false;
    }

    VisitedSet visited = {0};

    fprintf(out, "digraph NFA {\n");
    fprintf(out, "    rankdir=LR;\n");
    fprintf(out, "    node [shape=circle];\n");
    fprintf(out, "    __start [shape=point];\n");
    fprintf(out, "    __start -> q%d;\n", nfa->start->id);

    bool ok = emit_state_recursive(out, nfa->start, nfa->accept, &visited);

    fprintf(out, "}\n");

    visited_free(&visited);
    return ok;
}

bool export_nfa_dot(const NFA *nfa, const char *filename) {
    if (nfa == NULL || filename == NULL) {
        return false;
    }

    FILE *out = fopen(filename, "w");
    if (out == NULL) {
        return false;
    }

    bool ok = write_nfa_dot(out, nfa);

    if (fclose(out) != 0) {
        ok = false;
    }

    return ok;
}