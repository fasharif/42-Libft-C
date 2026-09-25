/* Tests for libft's own functions, mostly by comparison with the C library. */
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libft.h"

static int checks;
static int failures;

#define EXPECT(condition, name)                                                   \
    do {                                                                          \
        checks++;                                                                 \
        if (!(condition)) {                                                       \
            failures++;                                                           \
            fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, name);             \
        }                                                                         \
    } while (0)

static int same_sign(int a, int b) {
    return (a > 0) == (b > 0) && (a < 0) == (b < 0);
}

static void free_split(char **parts) {
    for (size_t i = 0; parts && parts[i]; i++)
        free(parts[i]);
    free(parts);
}

static void test_character_classes(void) {
    int alpha = 1, digit = 1, alnum = 1, print = 1, ascii = 1, upper = 1, lower = 1;

    for (int c = 0; c <= 255; c++) {
        alpha &= (ft_isalpha(c) != 0) == (isalpha(c) != 0);
        digit &= (ft_isdigit(c) != 0) == (isdigit(c) != 0);
        alnum &= (ft_isalnum(c) != 0) == (isalnum(c) != 0);
        print &= (ft_isprint(c) != 0) == (isprint(c) != 0);
        ascii &= (ft_isascii(c) != 0) == (c <= 127);
        upper &= ft_toupper(c) == toupper(c);
        lower &= ft_tolower(c) == tolower(c);
    }
    EXPECT(alpha, "ft_isalpha matches isalpha for 0-255");
    EXPECT(digit, "ft_isdigit matches isdigit for 0-255");
    EXPECT(alnum, "ft_isalnum matches isalnum for 0-255");
    EXPECT(print, "ft_isprint matches isprint for 0-255");
    EXPECT(ascii, "ft_isascii is true exactly for 0-127");
    EXPECT(upper, "ft_toupper matches toupper for 0-255");
    EXPECT(lower, "ft_tolower matches tolower for 0-255");
}

static void test_memory(void) {
    char a[32];
    char b[32];
    const char src[] = "0123456789abcdef";
    const char with_nul[] = "a\0b";

    memset(a, 'x', sizeof a);
    memset(b, 'x', sizeof b);
    memset(b, 'A', 10);
    EXPECT(ft_memset(a, 'A', 10) == a && memcmp(a, b, sizeof a) == 0, "ft_memset");

    memset(a, 'x', sizeof a);
    ft_bzero(a, 10);
    EXPECT(a[0] == 0 && a[9] == 0 && a[10] == 'x', "ft_bzero clears exactly n bytes");

    memset(a, 0, sizeof a);
    EXPECT(ft_memcpy(a, src, sizeof src) == a && strcmp(a, src) == 0, "ft_memcpy");

    strcpy(a, "0123456789");
    strcpy(b, "0123456789");
    ft_memmove(a + 2, a, 8);
    memmove(b + 2, b, 8);
    EXPECT(memcmp(a, b, 11) == 0, "ft_memmove with the destination after the source");
    strcpy(a, "0123456789");
    strcpy(b, "0123456789");
    ft_memmove(a, a + 2, 8);
    memmove(b, b + 2, 8);
    EXPECT(memcmp(a, b, 11) == 0, "ft_memmove with the destination before the source");

    EXPECT(ft_memchr(src, 'a', 16) == src + 10, "ft_memchr finds a byte");
    EXPECT(ft_memchr(src, 'z', 16) == NULL, "ft_memchr returns NULL when the byte is absent");
    EXPECT(ft_memchr(with_nul, 'b', 3) == with_nul + 2, "ft_memchr looks past a NUL byte");
    EXPECT(ft_memchr(src, 'a' + 256, 16) == src + 10, "ft_memchr compares c as an unsigned char");

    EXPECT(same_sign(ft_memcmp("abc", "abd", 3), memcmp("abc", "abd", 3)), "ft_memcmp");
    EXPECT(ft_memcmp("abc", "abd", 2) == 0, "ft_memcmp stops after n bytes");
    EXPECT(same_sign(ft_memcmp("a\200", "a\001", 2), memcmp("a\200", "a\001", 2)),
           "ft_memcmp compares unsigned bytes");

    int *zeros = ft_calloc(16, sizeof *zeros);
    int all_zero = zeros != NULL;
    for (int i = 0; zeros && i < 16; i++)
        all_zero &= zeros[i] == 0;
    EXPECT(all_zero, "ft_calloc returns zeroed memory");
    free(zeros);
    EXPECT(ft_calloc(SIZE_MAX / 2 + 2, 2) == NULL, "ft_calloc rejects a count * size that overflows");
}

static void test_strings(void) {
    const char *s = "hello world";
    char buf[8];

    EXPECT(ft_strlen("") == 0 && ft_strlen("hello") == 5, "ft_strlen");

    EXPECT(ft_strchr(s, 'o') == s + 4, "ft_strchr");
    EXPECT(ft_strchr(s, '\0') == s + 11, "ft_strchr finds the terminator");
    EXPECT(ft_strchr(s, 'z') == NULL, "ft_strchr returns NULL when absent");
    EXPECT(ft_strchr(s, 'o' + 256) == s + 4, "ft_strchr compares c as a char");
    EXPECT(ft_strrchr(s, 'o') == s + 7, "ft_strrchr");
    EXPECT(ft_strrchr(s, '\0') == s + 11, "ft_strrchr finds the terminator");
    EXPECT(ft_strrchr(s, 'z') == NULL, "ft_strrchr returns NULL when absent");

    EXPECT(same_sign(ft_strncmp("abc", "abd", 3), strncmp("abc", "abd", 3)), "ft_strncmp");
    EXPECT(ft_strncmp("abc", "abd", 2) == 0, "ft_strncmp stops after n characters");
    EXPECT(same_sign(ft_strncmp("ab", "abc", 5), strncmp("ab", "abc", 5)), "ft_strncmp on a shorter string");
    EXPECT(same_sign(ft_strncmp("a\200", "a\001", 2), strncmp("a\200", "a\001", 2)),
           "ft_strncmp compares unsigned characters");

    EXPECT(ft_strlcpy(buf, "hello world", sizeof buf) == 11 && strcmp(buf, "hello w") == 0,
           "ft_strlcpy truncates and returns the source length");
    EXPECT(ft_strlcpy(buf, "hi", 0) == 2, "ft_strlcpy with size 0 returns the source length");
    strcpy(buf, "abc");
    EXPECT(ft_strlcat(buf, "defgh", sizeof buf) == 8 && strcmp(buf, "abcdefg") == 0,
           "ft_strlcat truncates and returns the combined length");
    strcpy(buf, "abc");
    EXPECT(ft_strlcat(buf, "de", 2) == 4, "ft_strlcat with size below the destination length");

    const char *hay = "Foo Bar Baz";
    EXPECT(ft_strnstr(hay, "Bar", 11) == hay + 4, "ft_strnstr finds a needle");
    EXPECT(ft_strnstr(hay, "Bar", 6) == NULL, "ft_strnstr stops after len characters");
    EXPECT(ft_strnstr(hay, "", 3) == hay, "ft_strnstr with an empty needle returns the haystack");

    const char *numbers[] = {"0", "42", "-42", " \t\n+17abc", "2147483647", "-2147483648", "--5", "+-5", "007"};
    int atoi_ok = 1;
    for (size_t i = 0; i < sizeof numbers / sizeof *numbers; i++)
        atoi_ok &= ft_atoi(numbers[i]) == atoi(numbers[i]);
    EXPECT(atoi_ok, "ft_atoi matches atoi");

    char *copy = ft_strdup("copy me");
    EXPECT(copy && strcmp(copy, "copy me") == 0, "ft_strdup");
    free(copy);
}

static char add_index(unsigned int i, char c) {
    return (char)(c + (char)i);
}

static void upper_at_even(unsigned int i, char *c) {
    if (i % 2 == 0)
        *c = (char)toupper((unsigned char)*c);
}

static void test_allocating(void) {
    char *s;

    s = ft_substr("hello world", 6, 5);
    EXPECT(s && strcmp(s, "world") == 0, "ft_substr");
    free(s);
    s = ft_substr("hello", 10, 3);
    EXPECT(s && strcmp(s, "") == 0, "ft_substr starting past the end gives an empty string");
    free(s);
    s = ft_substr("hello", 1, 100);
    EXPECT(s && strcmp(s, "ello") == 0, "ft_substr stops at the end of the string");
    free(s);

    s = ft_strjoin("foo", "bar");
    EXPECT(s && strcmp(s, "foobar") == 0, "ft_strjoin");
    free(s);

    s = ft_strtrim("  xx hello xx  ", " x");
    EXPECT(s && strcmp(s, "hello") == 0, "ft_strtrim");
    free(s);
    s = ft_strtrim("xxxx", "x");
    EXPECT(s && strcmp(s, "") == 0, "ft_strtrim of nothing but set characters");
    free(s);

    char **parts = ft_split("  one two   three ", ' ');
    EXPECT(parts && parts[0] && strcmp(parts[0], "one") == 0 && parts[1] && strcmp(parts[1], "two") == 0
               && parts[2] && strcmp(parts[2], "three") == 0 && parts[3] == NULL,
           "ft_split skips repeated separators");
    free_split(parts);
    parts = ft_split("", ' ');
    EXPECT(parts && parts[0] == NULL, "ft_split of an empty string");
    free_split(parts);
    parts = ft_split("   ", ' ');
    EXPECT(parts && parts[0] == NULL, "ft_split of separators only");
    free_split(parts);

    const int values[] = {0, 7, -7, 42, INT_MAX, INT_MIN};
    int itoa_ok = 1;
    for (size_t i = 0; i < sizeof values / sizeof *values; i++) {
        char expected[16];
        snprintf(expected, sizeof expected, "%d", values[i]);
        s = ft_itoa(values[i]);
        itoa_ok &= s != NULL && strcmp(s, expected) == 0;
        free(s);
    }
    EXPECT(itoa_ok, "ft_itoa, including INT_MIN and INT_MAX");

    s = ft_strmapi("abc", add_index);
    EXPECT(s && strcmp(s, "ace") == 0, "ft_strmapi");
    free(s);
    char word[] = "abc";
    ft_striteri(word, upper_at_even);
    EXPECT(strcmp(word, "AbC") == 0, "ft_striteri");
}

static void test_output(void) {
    FILE *file = tmpfile();
    int fd = fileno(file);
    char buf[64] = {0};

    ft_putchar_fd('x', fd);
    ft_putstr_fd("hello", fd);
    ft_putendl_fd("line", fd);
    ft_putnbr_fd(INT_MIN, fd);
    ft_putnbr_fd(0, fd);
    ft_putnbr_fd(42, fd);
    lseek(fd, 0, SEEK_SET);
    ssize_t n = read(fd, buf, sizeof buf - 1);
    EXPECT(n > 0 && strcmp(buf, "xhelloline\n-2147483648042") == 0, "ft_putchar_fd, ft_putstr_fd, ft_putendl_fd, ft_putnbr_fd");
    fclose(file);
}

static void increment(void *content) {
    (*(int *)content)++;
}

static void *times_ten(void *content) {
    int *copy = malloc(sizeof *copy);
    if (copy)
        *copy = *(int *)content * 10;
    return copy;
}

static void keep(void *content) {
    (void)content;
}

static void test_lists(void) {
    int a = 1, b = 2, c = 3;
    t_list *list = NULL;

    ft_lstadd_back(&list, ft_lstnew(&b));
    ft_lstadd_front(&list, ft_lstnew(&a));
    ft_lstadd_back(&list, ft_lstnew(&c));
    EXPECT(ft_lstsize(list) == 3, "ft_lstsize");
    EXPECT(*(int *)list->content == 1 && *(int *)ft_lstlast(list)->content == 3,
           "ft_lstadd_front, ft_lstadd_back and ft_lstlast");
    ft_lstiter(list, increment);
    EXPECT(a == 2 && b == 3 && c == 4, "ft_lstiter");

    t_list *mapped = ft_lstmap(list, times_ten, free);
    EXPECT(mapped && ft_lstsize(mapped) == 3 && *(int *)mapped->content == 20
               && *(int *)ft_lstlast(mapped)->content == 40,
           "ft_lstmap");
    ft_lstclear(&mapped, free);
    EXPECT(mapped == NULL, "ft_lstclear empties the list");
    ft_lstclear(&list, keep);
    EXPECT(list == NULL && ft_lstsize(NULL) == 0 && ft_lstlast(NULL) == NULL, "ft_lstclear, and the empty list");
}

int main(void) {
    test_character_classes();
    test_memory();
    test_strings();
    test_allocating();
    test_output();
    test_lists();
    if (failures > 0) {
        fprintf(stderr, "libft: %d of %d checks failed\n", failures, checks);
        return 1;
    }
    printf("libft: all %d checks passed\n", checks);
    return 0;
}
