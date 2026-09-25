/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fasharif <fasharif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 16:54:06 by fasharif          #+#    #+#             */
/*   Updated: 2022/09/06 16:01:02 by fasharif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define GNL_MAX_FD 1024

char	*get_next_line(int fd);
char	*gnl_read_and_save(int fd, char *save);
char	*gnl_save(char *save);
char	*gnl_get_line(char *save);
size_t	gnl_strlen(char *str);
char	*gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);

#endif
