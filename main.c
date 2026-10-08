#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int is_keyword(const char* w) {
    static const char* KW[] = {"and","class","else","false","for","fun","if","nil",
        "or","print","return","super","this","true","var","while", NULL};
    for (int i = 0; KW[i]; i++) if (strcmp(KW[i], w) == 0) return 1;
    return 0;
}

int main(void) {
    char* src = NULL; size_t cap = 0; int c;
    size_t len = 0;
    while ((c = getchar()) != EOF) {
        if (len + 1 >= cap) { cap = cap ? cap * 2 : 64; src = realloc(src, cap); }
        src[len++] = (char)c;
    }
    if (src) src[len] = 0;

    int line = 1;
    for (size_t i = 0; i < len; ) {
        char ch = src[i];
        if (ch == '\n') { line++; i++; continue; }
        if (ch == ' ' || ch == '\r' || ch == '\t') { i++; continue; }
        switch (ch) {
            case '(': printf("LEFT_PAREN ( null\n"); i++; continue;
            case ')': printf("RIGHT_PAREN ) null\n"); i++; continue;
            // TODO: { } , . - + ; *
            // TODO: two-char ops (!=, ==, <=, >=)  and the BANG/EQUAL/LESS/GREATER variants
            // TODO: '/' may be SLASH or start a // comment
            // TODO: '"' STRING — track newlines, error if unterminated
            // TODO: digit -> NUMBER (with optional fraction)
            // TODO: alpha/_ -> IDENTIFIER, lookup with is_keyword()
        }
        i++;
    }
    printf("EOF  null\n");
    free(src);
    return 0;
}
