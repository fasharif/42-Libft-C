#include <string.h>
#include <stdio.h>
#include "libft.h"
                              lstadd-back or front
void	ft_print_result(t_list *elem)
{
	int		len;

	len = 0;
	while (((char *)elem->content)[len])
			len++;
	write(1, elem->content, len);
	write(1, "\n", 1);
}

t_list	*ft_lstnewone(void *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (!elem)
			return (NULL);
	if (!content)
			elem->content = NULL;
	else
			elem->content = content;
	elem->next = NULL;
	return (elem);
}

int	main(void)
{
	t_list		*begin;
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	char		*str = strdup("lorem");
	char		*str2 = strdup("ipsum");
	char		*str3 = strdup("dolor");
	char		*str4 = strdup("sit");

	elem = ft_lstnewone(str);
	elem2 = ft_lstnewone(str2);
	elem3 = ft_lstnewone(str3);
	elem4 = ft_lstnewone(str4);
	begin = NULL;
	ft_lstadd_back(&begin, elem);
	ft_lstadd_back(&begin, elem2);
	ft_lstadd_back(&begin, elem3);
	ft_lstadd_back(&begin, elem4);
	while (begin)
	{
		ft_print_result(begin);
		begin = begin->next;
	}
	return (0);
}
                                    lstclear

void	ft_print_result(t_list *elem)
{
	write(1, elem->content, strlen(elem->content));
}

static int	nb_free_done;

void	ft_del(void *content)
{
	free(content);
	nb_free_done++;
}

t_list	*ft_lstnewone(void *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (!elem)
			return (NULL);
	if (!content)
			elem->content = NULL;
	else
			elem->content = content;
	elem->next = NULL;
	return (elem);
}

int	main(void)
{
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	char		*str = strdup("lorem");
	char		*str2 = strdup("ipsum");
	char		*str3 = strdup("dolor");
	char		*str4 = strdup("sit");

	elem = ft_lstnewone(str);
	elem2 = ft_lstnewone(str2);
	elem3 = ft_lstnewone(str3);
	elem4 = ft_lstnewone(str4);
	elem->next = elem2;
	elem2->next = elem3;
	elem3->next = elem4;
	nb_free_done = 0;

	ft_lstclear(&elem3, &ft_del);
	if (elem)
		ft_print_result(elem);
	else
		write(1, "NULL", 4);
	write(1, "\n", 1);
	if (elem2)
		ft_print_result(elem2);
	else
		write(1, "NULL", 4);
	write(1, "\n", 1);
	if (elem3)
		ft_print_result(elem3);
	else
		write(1, "NULL", 4);
	write(1, "\n", 1);
	if (elem4)
	{
		write(1, "nb_free_done = ", 15);
		nb_free_done += '0';
		write(1, &nb_free_done, 1);
	}
	else
		write(1, "NULL", 4);
	return (0);
}
                                        lstdelone
void	ft_print_result(t_list *elem)
{
	int		len;

	len = 0;
	while (((char *)elem->content)[len])
			len++;
	write(1, elem->content, len);
	write(1, "\n", 1);
}

void	ft_del(void *content)
{
	free(content);
}

t_list	*ft_lstnewone(void *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (!elem)
			return (NULL);
	if (!content)
			elem->content = NULL;
	else
			elem->content = content;
	elem->next = NULL;
	return (elem);
}

int	main(void)
{
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	char		*str = strdup("lorem");
	char		*str2 = strdup("ipsum");
	char		*str3 = strdup("dolor");
	char		*str4 = strdup("sit");

	elem = ft_lstnewone(str);
	elem2 = ft_lstnewone(str2);
	elem3 = ft_lstnewone(str3);
	elem4 = ft_lstnewone(str4);
	elem->next = elem2;
	elem2->next = elem3;
	elem3->next = elem4;

	ft_lstdelone(elem3, &ft_del);
	if (elem)
		ft_print_result(elem);
	else
		write(1, "NULL", 4);
	write(1, "\n", 1);
	if (elem2)
		ft_print_result(elem2);
	else
		write(1, "NULL", 4);
	write(1, "\n", 1);
	if (elem4)
		ft_print_result(elem4);
	else
		write(1, "NULL", 4);

	return (0);
}
                                          lstiter
void	ft_modify_list_with_d(void *elem)
{
	int		len;
	char		*content;

	len = 0;
	content = (char *)elem;
	while (content[len])
		content[len++] = 'd';
}

void	ft_print_result(t_list *elem)
{
	int		len;

	while (elem)
	{
		len = 0;
		while (((char *)elem->content)[len])
			len++;
		write(1, elem->content, len);
		write(1, "\n", 1);
		elem = elem->next;
	}
}

t_list	*ft_lstnewone(void *content)
{
	t_list	*elem;
	elem = (t_list *)malloc(sizeof(t_list));

	if (!elem)
		return (NULL);
	if (!content)
		elem->content = NULL;
	else
		elem->content = content;
	elem->next = NULL;
	return (elem);
}

int	main(void)
{
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	char		*str = strdup("lorem");
	char		*str2 = strdup("ipsum");
	char		*str3 = strdup("dolor");
	char		*str4 = strdup("sit");

	elem = ft_lstnewone(str);
	elem2 = ft_lstnewone(str2);
	elem3 = ft_lstnewone(str3);
	elem4 = ft_lstnewone(str4);
	elem->next = elem2;
	elem2->next = elem3;
	elem3->next = elem4;

	ft_lstiter(elem, &ft_modify_list_with_d);
	ft_print_result(elem);

	return (0);
}
                                    lstlast
t_list	*ft_lstnewone(void *content)
{
	t_list	*elem;

	elem = (t_list *)malloc(sizeof(t_list));
	if (!elem)
		return (NULL);
	if (!content)
		elem->content = NULL;
	else
		elem->content = content;
	elem->next = NULL;
	return (elem);
}

int	main(void)
{
	int			i;
	char		*content;
	t_list		*val;
	t_list		*elem;
	t_list		*elem2;
	t_list		*elem3;
	t_list		*elem4;
	char		*str = strdup("lorem");
	char		*str2 = strdup("ipsum");
	char		*str3 = strdup("dolor");
	char		*str4 = strdup("sit");
	elem = ft_lstnewone(str);
	elem2 = ft_lstnewone(str2);
	elem3 = ft_lstnewone(str3);
	elem4 = ft_lstnewone(str4);

	elem->next = elem2;
	elem2->next = elem3;
	elem3->next = elem4;
	val = ft_lstlast(elem);
	i = 0;
	content = val->content;
	while (content[i])
		write(1, &(content[i++]), 1);
	write(1, "\n", 1);
	elem->next = NULL;
	val = ft_lstlast(elem);
	content = val->content;
}

                                      lstnew
void	ft_print_result(char const *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

int	main(void)
{
	t_list		*elem;	
	char str[]	= "lorem ipsum dolor sit";

	if (!(elem = ft_lstnew(str)))
		ft_print_result("NULL");
	else
	{
		if (!(elem->content))
			ft_print_result("NULL");
		else
		{
			ft_print_result(elem->content);
		}
		if (!(elem->next))
		{
			write(1, "\n", 1);
			ft_print_result("NULL");
		}
	}
	
	return (0);
}

                                    lstsize
void	ft_print_result(char const *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	write(1, s, len);
}

void	ft_print_result2(int n)
{
	char c;

	if (n >= 10)
		ft_print_result2(n / 10);
	c = n % 10 + '0';
	write (1, &c, 1);
}

int	main(void)
{
	t_list	*elem;

	char	str [] = "lorem ipsum dolor sit";
	int		i;

	if (!(elem = ft_lstnew(str)))
		ft_print_result("NULL");
	else
	{
		if (!(elem->content))
			ft_print_result("NULL");
		else
			ft_print_result(elem->content);
		if (!(elem->next))
		{
			write(1, "\n", 1);
			ft_print_result("NULL");
		}
	}

	write(1, "-", 1);

	i = 42;
