# libft

[![CI](https://github.com/fasharif/42-Libft-C/actions/workflows/ci.yml/badge.svg)](https://github.com/fasharif/42-Libft-C/actions/workflows/ci.yml)

My own C library, written for the 42 Abu Dhabi curriculum: re-implementations of common C
library functions, extra string and linked-list helpers, `ft_printf` and `get_next_line`, all
built into one static library, `libft.a`.

```bash
make                 # builds libft.a
make test            # builds and runs the tests
```

```c
#include "libft.h"   // compile with -I<path to this repository>, link with libft.a

int main(void)
{
    char *line = get_next_line(0);
    ft_printf("You typed: %s", line);
    free(line);
}
```

## What is inside

| Group | Functions |
| --- | --- |
| Characters | `ft_isalpha` `ft_isdigit` `ft_isalnum` `ft_isascii` `ft_isprint` `ft_toupper` `ft_tolower` |
| Memory | `ft_memset` `ft_bzero` `ft_memcpy` `ft_memmove` `ft_memchr` `ft_memcmp` `ft_calloc` |
| Strings (C library) | `ft_strlen` `ft_strlcpy` `ft_strlcat` `ft_strchr` `ft_strrchr` `ft_strncmp` `ft_strnstr` `ft_strdup` `ft_atoi` |
| Strings (extra) | `ft_substr` `ft_strjoin` `ft_strtrim` `ft_split` `ft_itoa` `ft_strmapi` `ft_striteri` |
| Output to a file descriptor | `ft_putchar_fd` `ft_putstr_fd` `ft_putendl_fd` `ft_putnbr_fd` |
| Linked lists | `ft_lstnew` `ft_lstadd_front` `ft_lstadd_back` `ft_lstsize` `ft_lstlast` `ft_lstdelone` `ft_lstclear` `ft_lstiter` `ft_lstmap` |
| Formatted output | `ft_printf`, supporting `%c %s %p %d %i %u %x %X %%` |
| Reading lines | `get_next_line`, which reads one line at a time from any number of file descriptors at once |

`ft_printf` and `get_next_line` were separate projects,
[42-Printf](https://github.com/fasharif/42-Printf) and
[42-get_next_line](https://github.com/fasharif/42-get_next_line). They now live here, in
[`ft_printf/`](ft_printf) and [`get_next_line/`](get_next_line), with their internal helpers
renamed (`pf_*`, `gnl_*`) so that they no longer clash with libft's own `ft_strlen`,
`ft_strjoin`, `ft_strchr` and `ft_itoa`.

## Testing

- [`tests/test_libft.c`](tests/test_libft.c) compares the functions with the C library where there
  is an equivalent, including edge cases such as `INT_MIN`, overlapping `memmove`, bytes above 127,
  and a `calloc` size that overflows.
- [`tests/test_printf.c`](tests/test_printf.c) checks `ft_printf`'s output and return value against
  `snprintf`, including one call that mixes every conversion.
- [`tests/test_gnl.c`](tests/test_gnl.c) reads files with and without a final newline, empty files,
  a 20,000-character line, and two files at once. It is built with `BUFFER_SIZE` 1, 42 and 10,000.

GitHub Actions runs the tests on Linux with GCC and Clang, on macOS on Apple Silicon, and under
AddressSanitizer, LeakSanitizer and UndefinedBehaviorSanitizer.

## License

[MIT](LICENSE)
