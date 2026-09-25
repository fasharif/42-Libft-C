/* Tests for ft_printf: what it prints and what it returns, captured from standard output. */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libft.h"

static int checks;
static int failures;
static char out[4096];

/* Runs ft_printf with standard output redirected to a temporary file, then reads it back. */
#define CAPTURE(result, ...)                                             \
    do {                                                                 \
        FILE *capture_file = tmpfile();                                  \
        int saved_stdout = dup(STDOUT_FILENO);                           \
        fflush(stdout);                                                  \
        dup2(fileno(capture_file), STDOUT_FILENO);                       \
        result = ft_printf(__VA_ARGS__);                                 \
        dup2(saved_stdout, STDOUT_FILENO);                               \
        close(saved_stdout);                                             \
        rewind(capture_file);                                            \
        size_t captured = fread(out, 1, sizeof out - 1, capture_file);   \
        out[captured] = '\0';                                            \
        fclose(capture_file);                                            \
    } while (0)

#define EXPECT_OUTPUT(expected_text, expected_count, ...)                                        \
    do {                                                                                         \
        int got;                                                                                 \
        checks++;                                                                                \
        CAPTURE(got, __VA_ARGS__);                                                               \
        if (got != (expected_count) || strcmp(out, (expected_text)) != 0) {                      \
            failures++;                                                                          \
            fprintf(stderr, "%s:%d: ft_printf(%s) printed \"%s\" and returned %d; "              \
                            "expected \"%s\" and %d\n",                                          \
                    __FILE__, __LINE__, #__VA_ARGS__, out, got, (expected_text), (int)(expected_count)); \
        }                                                                                        \
    } while (0)

/* For conversions where ft_printf and the C library should agree exactly. */
#define SAME_AS_PRINTF(...)                                         \
    do {                                                            \
        char want[4096];                                            \
        int want_count = snprintf(want, sizeof want, __VA_ARGS__);  \
        EXPECT_OUTPUT(want, want_count, __VA_ARGS__);               \
    } while (0)

int main(void) {
    int x = 42;
    void *ptr = &x;
    char pointer_text[64];

    SAME_AS_PRINTF("plain text");
    SAME_AS_PRINTF("%c%c%c", 'a', 'b', 'c');
    SAME_AS_PRINTF("[%s] [%s]", "one", "");
    SAME_AS_PRINTF("%d %i %d %d", 0, -42, INT_MAX, INT_MIN);
    SAME_AS_PRINTF("%u %u", 0u, 4294967295u);
    SAME_AS_PRINTF("%x %X %x", 255u, 3735928559u, 0u);
    SAME_AS_PRINTF("100%%");
    /* One call with every conversion: the va_list has to advance correctly between them. */
    SAME_AS_PRINTF("%c|%s|%d|%i|%u|%x|%X|%%|%c", 'z', "str", -1, 123, 456u, 48879u, 48879u, '!');

    snprintf(pointer_text, sizeof pointer_text, "%p", ptr);
    EXPECT_OUTPUT(pointer_text, (int)strlen(pointer_text), "%p", ptr);

    /* Where C libraries differ, ft_printf follows macOS. */
    EXPECT_OUTPUT("0x0", 3, "%p", NULL);
    EXPECT_OUTPUT("(null)", 6, "%s", (char *)NULL);
    /* A lone % at the end is dropped. */
    EXPECT_OUTPUT("abc", 3, "abc%");
    EXPECT_OUTPUT("", 0, "");

    if (failures > 0) {
        fprintf(stderr, "ft_printf: %d of %d checks failed\n", failures, checks);
        return 1;
    }
    printf("ft_printf: all %d checks passed\n", checks);
    return 0;
}
