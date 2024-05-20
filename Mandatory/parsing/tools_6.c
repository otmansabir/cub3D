/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:24:56 by osabir            #+#    #+#             */
/*   Updated: 2024/03/10 16:14:33 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

t_map	*ft_malloc(t_globel **globel)
{
	t_map	*map;

	map = NULL;
	if (!globel)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		ft_exit_error("Error malloc faild\n", globel);
	map->map = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->c = 0;
	map->f = 0;
	map->map_x = 0;
	map->map_y = 0;
	map->read = 0;
	return (map);
}

t_done	*give_value(t_globel **globel)
{
	t_done	*done;

	done = NULL;
	if (!globel)
		return (NULL);
	done = malloc(sizeof(t_done));
	if (!done)
		ft_exit_error("Error malloc faild\n", globel);
	done->no = false;
	done->so = false;
	done->we = false;
	done->ea = false;
	done->c = false;
	done->f = false;
	return (done);
}

int	ft_check_map(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (!ft_strchr("\n", line[i]))
			return (1);
		i++;
	}
	return (0);
}
