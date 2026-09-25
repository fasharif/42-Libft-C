# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/26 15:31:40 by fasharif          #+#    #+#              #
#    Updated: 2022/08/01 14:40:47 by fasharif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c ft_isprint.c \
	ft_putchar_fd.c ft_strlcat.c ft_substr.c ft_atoi.c ft_itoa.c ft_putendl_fd.c \
	ft_strlcpy.c ft_tolower.c ft_bzero.c ft_memcpy.c ft_putnbr_fd.c ft_strlen.c \
	ft_toupper.c ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c \
	ft_memcmp.c ft_split.c ft_strncmp.c ft_isalpha.c ft_strchr.c \
	ft_strnstr.c ft_isascii.c ft_memmove.c ft_strdup.c ft_strrchr.c ft_striteri.c
BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
	ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
PRINTF = ft_printf/ft_printf.c ft_printf/pf_putchar.c ft_printf/pf_putstr.c \
	ft_printf/pf_putnbr.c ft_printf/pf_puthex.c
GNL = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o) $(BONUS:.c=.o) $(PRINTF:.c=.o) $(GNL:.c=.o)
HEADERS = libft.h ft_printf/ft_printf.h get_next_line/get_next_line.h

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Everything, including the list functions, is built by default.
bonus: all

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
	$(CC) $(CFLAGS) $(LDFLAGS) -I. tests/test_libft.c $(NAME) -o tests/test_libft
	./tests/test_libft
	$(CC) $(CFLAGS) $(LDFLAGS) -I. tests/test_printf.c $(NAME) -o tests/test_printf
	./tests/test_printf
	for size in 1 42 10000; do \
		$(CC) $(CFLAGS) $(LDFLAGS) -I. -D BUFFER_SIZE=$$size tests/test_gnl.c $(GNL) -o tests/test_gnl \
		    && ./tests/test_gnl || exit 1; \
	done

clean:
	rm -f $(OBJS) tests/test_libft tests/test_printf tests/test_gnl

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus test clean fclean re
