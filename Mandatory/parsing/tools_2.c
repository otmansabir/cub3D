/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:05:52 by osabir            #+#    #+#             */
/*   Updated: 2024/03/10 18:07:24 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	if (need[0] == '\0')
		return ((char *)hay);
	if (len == 0)
		return (NULL);
	if (need == 0)
		return ((char *)hay);
	while (i < len && hay[i])
	{
		j = 0;
		while ((i + j) < len && hay[i + j] == need[j])
		{
			if (need[j + 1] == '\0')
				return ((char *)&hay[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

char	*check_side(char *line, t_globel **globel)
{
	char	*tmp;
	int		i;

	i = 2;
	if (!line || !globel)
		return (NULL);
	while (ft_strchr(" \t\v\r\f", line[i]))
		i++;
	tmp = ft_strdup("");
	while (line[i] != '\n' && line[i] != '\0')
	{
		tmp = ft_charjoin(tmp, line[i]);
		i++;
	}
	if (open(tmp, O_RDONLY) == -1)
		ft_exit_error("Error open file xpm\n", globel);
	return (tmp);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_test_forma(char *line, t_globel **globel)
{
	int	i;
	int	colon;

	i = 1;
	colon = 0;
	if (!line || !globel)
		return ;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_isdigit(line[i]) && !ft_strchr(", \t\v\r\f", line[i]))
			ft_exit_error("Error Not a correct format\n", globel);
		if (line[i] == ',')
			colon++;
		i++;
	}
	if (colon != 2)
		ft_exit_error("Error Not a correct format\n", globel);
}

int	color_nbr(char *line, t_globel **globel)
{
	t_color	color;
	char	**split;
	char	*copy;
	int		i;

	if (!line || !globel)
		return (0);
	copy = line;
	copy++;
	i = 0;
	split = ft_split(copy, ',');
	color.red = ft_atoi(split[0]);
	if (color.red > 255)
		ft_exit_error("Error red color > 255\n", globel);
	color.green = ft_atoi(split[1]);
	if (color.green > 255)
		ft_exit_error("Error green color > 255\n", globel);
	color.blue = ft_atoi(split[2]);
	if (color.blue > 255)
		ft_exit_error("Error blue color > 255\n", globel);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
	return ((color.red << 16) | (color.green << 8) | color.blue);
}
