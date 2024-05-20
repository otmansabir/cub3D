/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:05:48 by osabir            #+#    #+#             */
/*   Updated: 2024/03/11 10:54:21 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_func(t_globel **globel, char *line, bool x, bool y)
{
	if (!x && y)
		ft_exit_error("Error\n", globel);
	if (x)
		(*globel)->g_map->map
			= parsing_map(line, (*globel)->g_map->map, globel);
}

void	check_file_name(char *file_name, char *compre)
{
	int	i;
	int	j;

	if (!file_name || !compre)
		return ;
	i = ft_strlen(file_name);
	j = ft_strlen(compre);
	while (j > 0)
	{
		if (file_name[--i] != compre[--j])
			ft_exit_error("Error file name\n", NULL);
	}
	if (i > 0)
		return ;
	ft_exit_error("Error file name\n", NULL);
}

void	ft_readcheck(t_globel **globel)
{
	if (!globel)
		return ;
	if (!(*globel)->g_done->no || !(*globel)->g_done->so
		|| !(*globel)->g_done->we || !(*globel)->g_done->ea
		|| !(*globel)->g_done->c || !(*globel)->g_done->f
		|| !(*globel)->g_map->read)
	{
		ft_exit_error("Error\n", globel);
	}
}

void	ft_just_add(t_globel **globel)
{
	ft_readcheck(globel);
	(*globel)->g_map->map_x = len_map_x((*globel)->g_map->map, globel);
	(*globel)->g_map->map_y = len_map_y((*globel)->g_map->map, globel);
	ft_last_check_map((*globel)->g_map->map, globel);
	(*globel)->g_map->map
		= make_map_same_size((*globel)->g_map->map,
			(*globel)->g_map->map_x, (*globel)->g_map->map_y, globel);
}

t_map	*parsing_file(char *filename, t_globel *globel)
{
	int		fd;
	char	*line;

	if (!globel || !filename)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		ft_exit_error("Error open file\n", &globel);
	while (1)
	{
		line = get_line(fd, &globel);
		if (!line)
			break ;
		parsing_file_p2(&globel, line);
		free(line);
	}
	ft_just_add(&globel);
	close(fd);
	free(line);
	return (globel->g_map);
}
