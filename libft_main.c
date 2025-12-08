    atoi.c
int	main(void)
{
	char str[] = "89789";
	char str2[] = "-89789";

	printf("%d\n", ft_atoi(str));
	printf("%d\n", ft_atoi("1567"));
	printf("%d\n", ft_atoi(str2));
}
     bzero.c
int	main (void)
{
	char	data[20];
	size_t	n;

	n = 20;
	ft_bzero(data, n);
	printf("%s", data);
	return (0);
}
 isalpha or digits or printable or isascii
int	main(void)
{
	printf("%d it should be 0\n", ft_isalpha('5'));
	printf("%d it should be 1\n", ft_isalpha('z'));
	printf("%d it should be 0\n", ft_isalpha(9));
	printf("%d it should be 0\n", ft_isalpha(' '));
	printf("%d it should be 1\n", ft_isalpha('a'));
}
    itoa.c
int main(void)
{
	char	*result;
	int		numb;

	numb = 22141;
	result = ft_itoa(numb);
	printf("%d: %s\n", numb, result);
	numb = 2147483647;
	result = ft_itoa(numb);
	printf("%d: %s\n", numb, result);
	numb = -2147483648;
	result = ft_itoa(numb);
	printf("%d: %s\n", numb, result);
	numb = 0;
	result = ft_itoa(numb);
	printf("%d: %s\n", numb, result);
	return (0);
}

  main_memchr.c 
int	main (void)
{
	const char	str[] = "http://www.tutorialspoint.com";
	const char	ch = '.';
	char		*ret;

	ret = ft_memchr(str, ch, strlen(str));
	printf("String after |%c| is - |%s|\n", ch, ret);
	ret = memchr(str, ch, strlen(str));
	printf("String after |%c| is - |%s|\n", ch, ret);

	return (0);
}
  main_memcpy.c
int    main (void)
{
    char    mem_dest[20];
    char    mem_src[] = "alo bom dia";
    size_t    n;
	char	*pointer;

	n = 5;
	printf("test");
	pointer = ft_memcpy(mem_dest, mem_src, n);
    printf("test");
	printf("My function output: %s\n", pointer);
  return (0);
}
  main_memmove.c
int main ()
{
    char dest[] = "Aticleworld";
    const char src[]  = "Amlendra";
	//Source and destination before memmove
    printf("Before ft_memmove >> dest = %s, src = %s\n\n", dest, src);
    ft_memmove(dest, src, 5);
    //Source and destination after memmove
    printf("After ft_memmove >> dest = %s, src = %s\n\n", dest, src);
    return 0;
    //Source and destination before memmove
    printf("Before memmove >> dest = %s, src = %s\n\n", dest, src);
    memmove(dest, src, 5);
    //Source and destination after memmove
    printf("After memmove >> dest = %s, src = %s\n\n", dest, src);

}
  main_memcmp.c
int	main(void)
{
	char	str1[15];
	char	str2[15];
	int		ret;

	memcpy(str1, "abcdef", 6);
	memcpy(str2, "ABCDEF", 6);
	ret = ft_memcmp(str1, str2, 5);
	if (ret > 0)
		printf("str2 is less than str1");
	else if (ret < 0)
		printf("str1 is less than str2");
	else
		printf("str1 is equal to str2");
	return (0);
}
  main_memset.c
int	main (void)
{
	char	data[20];

	printf("%p\n", ft_memset(data, '\0', 20));
	printf("%p\n", memset(data, '\0', 20));
	//printf("%s\n", memset(data, '\0', 20));
	printf("%p\n", memset(data, 'A', 20));
	printf("%p\n", ft_memset(data, 'A', 10));
	//printf("%s\n", memset(data, 'A', 10));
	return (0);
}
    spilt.c
int	main(void)
{
	char	**splitted_str;
	splitted_str = ft_split("jan,,,fe44v,,,m555ar,working?", ',');
	printf("word1:%s | word2: %s | word3:%s | word4:%s\n", splitted_str[0],
		splitted_str[1], splitted_str[2], splitted_str[3]);
	return (0);
}
	main_strchr.c or strrchr
int	main (void)
{
	const char	str[] = "http://www.tutorialspoint.com";
	const char	ch = '.';
	char		*ret;

	ret = ft_strchr(str, ch);
	printf("String after ft_strchr |%c| is - |%s|\n", ch, ret);
	ret = strchr(str, ch);
	printf("String after   strchr |%c| is - |%s|\n", ch, ret);
	return (0);
}
	main_strdup.c
int	main(void)
{
	char	*src;
	char	*dup;

	src = "Farahhhhhhhhhhhhhhhhhhhhhhhh";
	dup = ft_strdup(src);
	printf ("src = %s and dup = %s\n", src, dup);
	return (0);
}
	 main_strjoin.c 
 int main()
{
	char *str1 = "let's see";
	char *str2 = " how this works";
	printf("%s\n", ft_strjoin(str1, str2));
}
	 main_strlcat.c
int main(void)
{
	int	s;
	int	r;

	s = -1;
	while (++s <= 13)
	{
		char	src[5] = "casa";
		char	dst[9] = "amor";
		if (s < 1)
		{
			printf("src:%s |dst:%s\n", src, dst);
			printf("r = strlcat(dst, src, size)\n");
		}
		r = strlcat(dst, src, s);
		printf("size:%d | src:%s | dst:%s | return: %d\n", s, src, dst, r);
	}
		 return (0);
	 }
		main_strlcpy.c
int	main(void)
{
	int 	src_size;
	char 	*src;
	char 	*dest;

	src = ft_calloc(11, sizeof(char));
	dest = ft_calloc(8, sizeof(char));
	src = "alo galera";
	src_size = ft_strlcpy(dest, src, 8);
	printf("src: %s\n", src);
	printf("dest: %s\n", dest);
	printf("src_size: %d\n", src_size);
	return(0);
}
main_strncmp.c
int	main(void)
{
	char	str1[15];
	char	str2[15];
	int		ret;

	ft_memcpy(str1, "abcdef", 6);
	ft_memcpy(str2, "ABCDEF", 6);
	ret = ft_strncmp(str1, str2, 5);
	if (ret > 0)
		printf("str2 is less than str1\n");
	else if (ret < 0)
		printf("str1 is less than str2\n");
	else
		printf("str1 is equal to str2\n");
	return (0);
}
	 main_strnstr.c 
int	main(void)
{
	char	*str1;
	char	*str2;

	str1 = "dalibftd\0a";
	str2 = "libft";
	printf("My function output: %s\n", ft_strnstr(str1, str2, 12));
	return (0);
}
	 main_strtrim.c  
 int	main(void)
{
	char	*str;
	char	*set;

	str = "abc affffff abc";
	set = "abc";
	printf("%s", ft_strtrim(str, set));
	return (0);
}
  main_substr.c
int	main(void)
{
	char *str;
	char *substr;

	str = "topa tudo por";
	substr = ft_substr(str, 1, 10);
	printf ("%s should be a substr of %s", substr, str);
	return (0);
}
