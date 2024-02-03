#include "cub3d.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	res = 0;
	j = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			j = j * -1;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] >= '0' && str[i] <= '9')
			res = res * 10;
		res = res + (str[i] - 48);
		if (res > 255)
			return (res * j);
		i++;
	}
	return (res * j);
}


static size_t	ft_cw(char const *s, char c)
{
	size_t	j;
	size_t	w;

	j = 0;
	w = 0;
	if (s[0] == '\0')
		return (0);
	if (s[0] != c)
	{
		j++;
		w++;
	}
	while (s[j] != '\0')
	{
		if (s[j] == c && s[j + 1] != c && s[j + 1] != '\0')
			w++;
		j++;
	}
	return (w);
}

static size_t	ft_clen(char const *s, char c, size_t len)
{
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

static char	**ft_free(char	**str, int i)
{
	int	n;

	n = 0;
	while (n <= i)
	{
		free(str[n]);
		n++;
	}
	free(str);
	return (NULL);
}

static char	**ft_splitv2(char **str, char const *s, char c, size_t count)
{
	size_t	len;
	size_t	start;
	size_t	i;

	start = 0;
	i = 0;
	while (i < count)
	{
		while (s[start] == c)
			start++;
		len = ft_clen(s, c, start);
		str[i] = ft_substr(s, start, (len - start));
		if (str[i] == NULL)
			return (ft_free(str, i));
		start = 0;
		start += len;
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	count;

	if (!s)
		return (NULL);
	count = ft_cw(s, c);
	str = malloc(((count + 1) * sizeof(char *)));
	if (!str)
		return (NULL);
	str = ft_splitv2(str, s, c, count);
	return (str);
}

char	*ft_charjoin(char *s1, char c)
{
	char	*str;
	int		j;
	int		o;

	if (!s1 || !c)
	{
		printf("s1 = %s || %c\n", s1, c);
		return (NULL);
	}
	str = malloc(ft_strlen(s1) + 2);
	if (!str)
		exit(1);
	j = 0;
	o = 0;
	while (s1[j] != '\0')
		str[o++] = s1[j++];
	str[o++] = c;
	str[o] = '\0';
	free(s1);
	return (str);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*b1;
	unsigned char	*b2;
	size_t			j;

	b1 = (unsigned char *)dst;
	b2 = (unsigned char *)src;
	if (dst == src)
		return (dst);
	if (!b1 && !b2)
		return (NULL);
	j = 0;
	while (j < n)
	{
		b1[j] = b2[j];
		j++;
	}
	return (b1);
}

char	*ft_strdup(const char *s1)
{
	char	*str;

	str = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!str)
		return (NULL);
	return (ft_memcpy(str, (char *)s1, ft_strlen(s1) + 1));
}