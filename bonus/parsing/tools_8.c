/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:28:44 by osabir            #+#    #+#             */
/*   Updated: 2024/03/11 10:55:37 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**to_arry(char *line, char **map)
{
	char	**s;
	int		j;
	int		index;

	j = 0;
	s = NULL;
	if (!line)
		return (NULL);
	index = 0;
	while (map[j] != NULL)
		j++;
	s = malloc((j + 2) * sizeof(char *));
	if (!s)
		exit(1);
	while (index < j)
	{
		s[index] = ft_strdup(map[index]);
		index++;
	}
	s[index++] = ft_strdup(line);
	s[index] = NULL;
	return (s);
}

char	**parsing_map(char *line, char **map, t_globel **globel)
{
	char	**s;
	int		i;

	i = 0;
	s = NULL;
	if (!line || !globel)
		return (NULL);
	char_map(line, globel);
	while (line[i] && line[i] != '\n' && line[i] != '\0')
	{
		if (ft_strchr("0SWEN", line[i]))
		{
			if (!left_side(line, i) || !right_side(line, i))
				ft_exit_error("Error wall not close\n", globel);
		}
		i++;
	}
	if (map == NULL)
		return (one_arry(line));
	else
		s = to_arry(line, map);
	add_this_function(globel, map);
	return (s);
}

int	len_map_x(char **map, t_globel **globel)
{
	int	i;
	int	j;
	int	lenght;

	i = 0;
	j = 0;
	lenght = 0;
	if (!map || !(*map) || !globel)
		return (0);
	if (*map == NULL)
		ft_exit_error("Error you dont have a map\n", globel);
	while (map[i])
	{
		j = ft_strlen(map[i]) - 1;
		if (j > lenght)
			lenght = j;
		i++;
	}
	return (lenght);
}

int	len_map_y(char **map, t_globel **globel)
{
	int	i;

	i = 0;
	if (!map || !(*map) || !globel)
		return (0);
	if (*map == NULL)
		ft_exit_error("Error you dont have a map\n", globel);
	while (map[i])
		i++;
	if (i <= 2)
		ft_exit_error("Error you dont have a map\n", globel);
	return (i);
}

void	ft__last_check_map(char **map, t_plyr *plyr, t_globel **globel)
{
	if (!map || !(*map) || !globel)
		return ;
	while (map[plyr->i][plyr->j] && map[plyr->i][plyr->j] != '\0')
	{
		if (ft_strchr("SWEN", map[plyr->i][plyr->j]))
		{
			if (!(plyr->player_in_map))
				(plyr->player_in_map) = true;
			else
				ft_exit_error("Error you have more than one player\n", globel);
		}
		if (ft_strchr("0SWEN", map[plyr->i][plyr->j]))
		{
			if (!ft_left(map, plyr->i, plyr->j)
				|| !ft_right(map, plyr->i, plyr->j)
				|| !ft_down(map, plyr->i, plyr->j)
				|| !ft_up(map, plyr->i, plyr->j))
				ft_exit_error("Error wall not close\n", globel);
		}
		plyr->j++;
	}
}
