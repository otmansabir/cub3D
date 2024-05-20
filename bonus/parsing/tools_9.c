/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_9.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:31:29 by osabir            #+#    #+#             */
/*   Updated: 2024/03/11 10:55:55 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	ft_left(char **line, int i, int j)
{
	if (!line || !(*line))
		return (false);
	while (j >= 0)
	{
		if (line[i][j] == '1')
			return (true);
		if (ft_strchr(" \n\t", line[i][j]))
			return (false);
		j--;
	}
	return (false);
}

bool	ft_right(char **line, int i, int j)
{
	if (!line || !(*line))
		return (false);
	while (line[i][j] != '\0')
	{
		if (line[i][j] == '1')
			return (true);
		if (ft_strchr(" \n\t", line[i][j]))
			return (false);
		j++;
	}
	return (false);
}

bool	ft_down(char **line, int i, int j)
{
	if (!line || !(*line))
		return (false);
	while (line[i])
	{
		if (line[i][j] == '1')
			return (true);
		if (ft_strchr(" \n\t", line[i][j]))
			return (false);
		i++;
	}
	return (false);
}

bool	ft_up(char **line, int i, int j)
{
	if (!line || !(*line))
		return (false);
	while (line[i] && i > -1)
	{
		if (line[i][j] == '1')
			return (true);
		if (ft_strchr(" \n\t", line[i][j]))
			return (false);
		i--;
	}
	return (false);
}

void	ft_last_check_map(char **map, t_globel **globel)
{
	t_plyr	plyr;

	plyr.i = 0;
	if (!map || !(*map) || !globel)
		return ;
	plyr.player_in_map = false;
	while (map[plyr.i])
	{
		plyr.j = 0;
		ft__last_check_map(map, &plyr, globel);
		plyr.i++;
	}
	if (!plyr.player_in_map)
		ft_exit_error("Error map without any player\n", globel);
}
