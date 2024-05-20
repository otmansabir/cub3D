/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:21:38 by osabir            #+#    #+#             */
/*   Updated: 2024/03/10 10:39:25 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

char	*ft_charjoin(char *s1, char c)
{
	char	*str;
	int		j;
	int		o;

	if (!s1 || !c)
		return (NULL);
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

char	*ft_strdup(const char *s1)
{
	char	*str;

	str = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!str)
		return (NULL);
	return (ft_memcpy(str, (char *)s1, ft_strlen(s1) + 1));
}
