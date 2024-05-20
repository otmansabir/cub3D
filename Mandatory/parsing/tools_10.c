/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:32:55 by osabir            #+#    #+#             */
/*   Updated: 2024/03/11 10:54:53 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*new_line(char *line, int size_map, t_globel **globel)
{
	char	*map_line;
	int		i;

	if (!line || !globel)
		return (NULL);
	map_line = malloc((size_map + 1) * sizeof(char *));
	if (!map_line)
		ft_exit_error("Error malloc faild\n", globel);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (ft_strchr(" \n\t", line[i]))
			map_line[i] = '2';
		else
			map_line[i] = line[i];
		i++;
	}
	if (i < size_map)
	{
		while (i < size_map)
			map_line[i++] = '2';
	}
	map_line[i] = '\0';
	return (map_line);
}

char	**make_map_same_size(char **map, int len,
int size_map, t_globel **globel)
{
	char	**line;
	int		i;

	i = 0;
	if (!map || !(map) || !globel)
		return (NULL);
	line = malloc((size_map + 1) * sizeof(char *));
	if (!line)
		ft_exit_error("Error mallc faild\n", globel);
	while (map[i])
	{
		line[i] = new_line(map[i], len, globel);
		i++;
	}
	line[i] = NULL;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	return (line);
}

void	ft_no(t_globel **globel, char *line)
{
	if (!globel || !(*globel) || !line)
		return ;
	if (!(*globel)->g_done->no)
		(*globel)->g_map->no = check_side(line, globel);
	else
		ft_exit_error("Error dublcatet line\n", globel);
	(*globel)->g_done->no = true;
}

void	parsing_file_p2(t_globel **globel, char *line)
{
	if (!globel || !(*globel) || !line)
		return ;
	if (ft_strnstr(line, "NO ", ft_strlen(line)))
		ft_no(globel, line);
	else if (ft_strnstr(line, "SO ", ft_strlen(line)))
		ft_so(globel, line);
	else if (ft_strnstr(line, "WE ", ft_strlen(line)))
		ft_we(globel, line);
	else if (ft_strnstr(line, "EA ", ft_strlen(line)))
		ft_ea(globel, line);
	else if (ft_strnstr(line, "F ", ft_strlen(line)))
		ft_f(globel, line);
	else if (ft_strnstr(line, "C ", ft_strlen(line)))
		ft_c(globel, line);
	else if (ft_check_map(line))
		ft_map(globel, line);
}

void	ft_map(t_globel **globel, char *line)
{
	bool	x;
	bool	y;
	int		i;

	x = false;
	y = false;
	i = 0;
	if (!globel || !(*globel) || !line)
		return ;
	if (!(*globel)->g_done->no || !(*globel)->g_done->so
		|| !(*globel)->g_done->we || !(*globel)->g_done->ea
		|| !(*globel)->g_done->c || !(*globel)->g_done->f)
		ft_exit_error("Error info of map not complete\n", globel);
	while (line[i])
	{
		if (ft_strchr("10SWEN", line[i]))
			x = true;
		if (ft_strchr("\n \t", line[i]))
			y = true;
		i++;
	}
	check_func(globel, line, x, y);
}
