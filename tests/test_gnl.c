/* Tests for get_next_line. The Makefile builds this file with several BUFFER_SIZE values. */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "get_next_line/get_next_line.h"

static int checks;
static int failures;

#define EXPECT(condition, name)                                                   \
    do {                                                                          \
        checks++;                                                                 \
        if (!(condition)) {                                                       \
            failures++;                                                           \
            fprintf(stderr, "%s:%d: BUFFER_SIZE=%d: %s\n", __FILE__, __LINE__,    \
                    BUFFER_SIZE, name);                                           \
        }                                                                         \
    } while (0)

/* Writes content to a temporary file and returns it open for reading. */
static int open_with(const char *content) {
    char path[] = "/tmp/gnl_test_XXXXXX";
    int fd = mkstemp(path);

    if (fd < 0 || write(fd, content, strlen(content)) != (ssize_t)strlen(content)) {
        perror("creating a test file");
        exit(2);
    }
    close(fd);
    fd = open(path, O_RDONLY);
    unlink(path);
    return fd;
}

/* True if get_next_line returns exactly these lines, then NULL. */
static int reads_back(const char *content, const char *const *lines) {
    int fd = open_with(content);
    int ok = 1;

    for (size_t i = 0; lines[i] != NULL; i++) {
        char *line = get_next_line(fd);
        ok &= line != NULL && strcmp(line, lines[i]) == 0;
        free(line);
    }
    char *end = get_next_line(fd);
    ok &= end == NULL;
    free(end);
    close(fd);
    return ok;
}

int main(void) {
    const char *const three[] = {"one\n", "two\n", "three\n", NULL};
    const char *const no_final_newline[] = {"first\n", "last", NULL};
    const char *const nothing[] = {NULL};
    const char *const blank_lines[] = {"\n", "\n", "x\n", NULL};

    EXPECT(reads_back("one\ntwo\nthree\n", three), "reads lines that end in a newline");
    EXPECT(reads_back("first\nlast", no_final_newline), "returns a last line without a newline");
    EXPECT(reads_back("", nothing), "returns NULL for an empty file");
    EXPECT(reads_back("\n\nx\n", blank_lines), "returns empty lines");

    char *long_text = malloc(20002);
    if (long_text == NULL)
        return 2;
    memset(long_text, 'a', 20000);
    long_text[20000] = '\n';
    long_text[20001] = '\0';
    const char *const long_line[] = {long_text, NULL};
    EXPECT(reads_back(long_text, long_line), "reads a line of 20,000 characters");
    free(long_text);

    int a = open_with("a1\na2\n");
    int b = open_with("b1\nb2\n");
    const int fds[] = {a, b, a, b, a, b};
    const char *const expected[] = {"a1\n", "b1\n", "a2\n", "b2\n", NULL, NULL};
    int interleaved = 1;
    for (int i = 0; i < 6; i++) {
        char *line = get_next_line(fds[i]);
        if (expected[i] == NULL)
            interleaved &= (line == NULL);
        else
            interleaved &= (line != NULL && strcmp(line, expected[i]) == 0);
        free(line);
    }
    close(a);
    close(b);
    EXPECT(interleaved, "keeps a separate position for each file descriptor");

    EXPECT(get_next_line(-1) == NULL, "rejects a negative file descriptor");
    EXPECT(get_next_line(GNL_MAX_FD) == NULL, "rejects a descriptor past the end of its table");
    EXPECT(get_next_line(GNL_MAX_FD - 1) == NULL, "returns NULL when read() fails");

    if (failures > 0) {
        fprintf(stderr, "get_next_line (BUFFER_SIZE=%d): %d of %d checks failed\n", BUFFER_SIZE, failures, checks);
        return 1;
    }
    printf("get_next_line (BUFFER_SIZE=%d): all %d checks passed\n", BUFFER_SIZE, checks);
    return 0;
}
