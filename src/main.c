#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "struct_parser.h"
#include "struct_nfa.h"
#include "rec_desc_parser.h"
#include "nfa_dot_export.h"

static void print_usage(const char *prog_name) {
    fprintf(stderr, "Usage: %s <regex> <output.dot>\n", prog_name);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    const char *regex_input = argv[1];
    const char *dot_output = argv[2];

    Parser parser;
    parser.input = (char *)regex_input;
    parser.pos = 0;

    NFA result;

    if (!parse_expr(&parser, &result)) {
        fprintf(stderr, "Error: failed to parse regex.\n");
        return EXIT_FAILURE;
    }

    if (parser.input[parser.pos] != '\0') {
        fprintf(stderr, "Error: trailing characters after valid regex at position %zu.\n",
                parser.pos);
        return EXIT_FAILURE;
    }

    if (!export_nfa_dot(&result, dot_output)) {
        fprintf(stderr, "Error: failed to write DOT file '%s'.\n", dot_output);
        return EXIT_FAILURE;
    }

    printf("DOT file written to %s\n", dot_output);
    return EXIT_SUCCESS;
}