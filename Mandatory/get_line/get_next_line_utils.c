/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:05:36 by osabir            #+#    #+#             */
/*   Updated: 2024/02/27 11:08:53 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = malloc(count * size);
	if (!str)
		return (NULL);
	ft_memset((char *)str, 0, (count * size));
	return (str);
}

void	ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			j;

	str = (unsigned char *)b;
	j = 0;
	while (j < len)
	{
		str[j] = (unsigned char)c;
		j++;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (*s == '\0')
		return (NULL);
	j = ft_strlen(s);
	i = 0;
	if (start >= j)
		start = j;
	if (len > j - start)
		len = (j - start);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	if (s)
	{
		while (i < len && s[start])
			str[i++] = s[start++];
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	int		j;

	j = 0;
	while (s && s[j] != '\0' && s[j] != (char)c)
		j++;
	if (s && s[j] == (char)c)
		return ((char *)(s + j));
	return (NULL);
}
