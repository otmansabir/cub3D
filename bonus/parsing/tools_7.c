/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:27:08 by osabir            #+#    #+#             */
/*   Updated: 2024/03/11 10:55:26 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	add_this_function(t_globel **globel, char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
	(*globel)->g_map->read = 1;
}

void	char_map(char *line, t_globel **globel)
{
	int	i;

	i = 0;
	if (!line || !globel)
		return ;
	while (line[i])
	{
		if (ft_strchr(" \t01SWEN\n", line[i]))
			i++;
		else
			ft_exit_error("Error an identifier char\n", globel);
	}
}

bool	right_side(char *line, int i)
{
	if (!line)
		return (false);
	while (line[i] && line[i] != '\0')
	{
		if (line[i] == '1')
			return (true);
		else if (ft_strchr(" \t\n\0", line[i]))
			return (false);
		i++;
	}
	return (false);
}

bool	left_side(char *line, int i)
{
	if (!line)
		return (false);
	while (i >= 0)
	{
		if (line[i] == '1')
			return (true);
		else if (ft_strchr(" \t\n\0", line[i]))
			return (false);
		i--;
	}
	return (false);
}

char	**one_arry(char *line)
{
	char	**s;

	s = NULL;
	if (!line)
		return (NULL);
	s = malloc(2 * sizeof(char *));
	if (!s)
		exit(1);
	s[0] = ft_strdup(line);
	s[1] = NULL;
	return (s);
}
