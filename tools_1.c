#include "cub3d.h"

void	ft_free_t_map_and_error(t_map **map)
{
	int	i;

	i = 0;
	if ((*map)->map)
	{
		while ((*map)->map[i])
			free((*map)->map[i++]);
	}
	if ((*map)->no)
		free((*map)->no);
	if ((*map)->so)
		free((*map)->so);
	if ((*map)->we)
		free((*map)->we);
	if ((*map)->ea)
		free((*map)->ea);
	(*map)->map = NULL;
	(*map)->no = NULL;
	(*map)->so = NULL;
	(*map)->we = NULL;
	(*map)->ea = NULL;
	
}

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

t_map	*ft_malloc(t_map **map)
{
	*map = malloc(sizeof(t_map));
	if (*map == NULL)
		ft_exit_error("malloc faild\n");
	(*map)->map = NULL;
	(*map)->no = NULL;
	(*map)->so = NULL;
	(*map)->we = NULL;
	(*map)->ea = NULL;
	return (*map);
}

t_done	*give_value(t_done *done)
{
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
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("01SWEN", line[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_error_char(void)
{
	write(2, "an identifier char\n", 19);
	exit(1);
}

void	char_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(" \t01SWEN\n", line[i]))
			i++;
		else
			ft_error_char();
	}
}

bool	right_side(char *line, int i)
{
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

char	**parsing_map(char *line, char **map)
{
	char	**s;
	int		i;
	int		j;
	int		index;

	i = 0;
	j = 0;
	index = 0;
	s = NULL;
	char_map(line);
	while (line[i] && line[i] != '\n' && line[i] != '\0')
	{
		if (ft_strchr("0SWEN", line[i]))
		{
			if (!left_side(line, i) || !right_side(line, i))
			{
				write(2, "error wall not close\n", 21);
				exit(1);
			}
		}
		i++;
	}
	if (map == NULL)
	{
		
		s = (char **)malloc(2 * sizeof(char **));
		if (!s)
			exit(1);
		s[0] = ft_strdup(line);
		s[1] = NULL;
		return (s);
	}
	else
	{
		while (map[j] != NULL)
			j++;
		s = (char **)malloc((j + 2) * sizeof(char **));
		if (!s)
			exit(1);
		while (index < j)
		{
			s[index] = ft_strdup(map[index]);
			index++;
		}
		s[index++] = ft_strdup(line);
		s[index] = NULL;
	}
	i = 0;
	while (map[i])
	{
		free(map[i++]);
	}
	free(map);
	return (s);
}

int	len_map_x(char **map)
{
	int	i;
	int	j;
	int	lenght;

	i = 0;
	j = 0;
	lenght = 0;
	if (*map == NULL)
	{
		write(2, "you dont have a map\n", 20);
		exit(1);
	}
	while (map[i])
	{
		j = ft_strlen(map[i]) - 1;
		if (j > lenght)
			lenght = j;
		i++;
	}
	return (lenght);
}

int	len_map_y(char **map)
{
	int	i;

	i = 0;
	if (*map == NULL)
	{
		write(2, "you dont have a map\n", 20);
		exit(1);
	}
	while (map[i])
		i++;
	if (i <= 2)
	{
		write(2, "you dont have a map\n", 20);
		exit(1);
	}
	return (i);
}

bool	ft_left(char **line, int i, int j)
{
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

void	ft_last_check_map(char **map)
{
	bool	zero_in_map;
	bool	player_in_map;
	int	i;
	int	j;

	i = 0;
	zero_in_map = false;
	player_in_map = false;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\0')
		{
			if (!zero_in_map && map[i][j] == '0')
				zero_in_map = true;
			if (ft_strchr("SWEN", map[i][j]))
			{
				if (!player_in_map)
					player_in_map = true;
				else
				{
					write(2, "error you have more than one player\n", 36);
					exit(1);
				}
			}
			if (ft_strchr("0SWEN", map[i][j]))
			{
				if (!ft_left(map, i, j) || !ft_right(map, i, j)
					|| !ft_down(map, i, j) || !ft_up(map, i, j))
				{
					write(2, "error wall not close\n", 21);
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
	if (!zero_in_map)
	{
		write(2, "map not have zero\n", 18);
		exit(1);
	}
	if (!player_in_map)
	{
		write(2, "map without any player\n", 23);
		exit(1);
	}
}

char	*new_line(char *line, int size_map)
{
	char	*map_line;
	int		i;

	map_line = malloc(size_map);
	if (!map_line)
		exit(1);
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

char	**make_map_same_size(char **map, int len, int size_map)
{
	char	**line;
	int		i;

	i = 0;
	line = (char **)malloc((size_map + 1) * (sizeof(char **)));
	if (!line)
		exit(1);
	while (map[i])
	{
		line[i] = new_line(map[i], len);
		free(map[i]);
		i++;
	}
	line[i] = NULL;
	return (line);
}

t_map	*parsing_file(char *filename, t_globel *globle)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open file");
		exit(1);
	}
	while (1)
	{
		line = get_line(fd);
		if (!line)
			break ;
		if (ft_strnstr(line, "NO ", ft_strlen(line)))
		{
			if (!globle->g_done->no)
				globle->g_map->no = check_side(line);
			else
			{
				write(2, "error dublcatet line\n", 21);
				exit(1);
			}
			globle->g_done->no = true;
		}
		else if (ft_strnstr(line, "SO ", ft_strlen(line)))
		{
			if (!globle->g_done->so)
				globle->g_map->so = check_side(line);
			else
			{
				write(2, "error dublcatet line\n", 21);
				exit(1);
			}
			globle->g_done->so = true;
		}
		else if (ft_strnstr(line, "WE ", ft_strlen(line)))
		{
			if (!globle->g_done->we)
				globle->g_map->we = check_side(line);
			else
			{
				write(2, "error dublcatet line: WE\n", 25);
				exit(1);
			}
			globle->g_done->we = true;
		}
		else if (ft_strnstr(line, "EA ", ft_strlen(line)))
		{
			if (!globle->g_done->ea)
				globle->g_map->ea = check_side(line);
			else
			{
				write(2, "error dublcatet line\n", 21);
				exit(1);
			}
			globle->g_done->ea = true;
		}
		else if (ft_strnstr(line, "F ", ft_strlen(line)))
		{
			if (!globle->g_done->f)
			{
				globle->g_map->f = checkside2(line);
			}
			else
			{
				write(2, "error dublcatet line\n", 21);
				exit(1);
			}
			globle->g_done->f = true;
		}
		else if (ft_strnstr(line, "C ", ft_strlen(line)))
		{
			if (!globle->g_done->c)
			{
				globle->g_map->c = checkside2(line);
			}
			else
			{
				write(2, "error dublcatet line\n", 21);
				exit(1);
			}
			globle->g_done->c = true;
		}
		else if (ft_check_map(line))
		{
			if (!globle->g_done->no || !globle->g_done->so || !globle->g_done->we || !globle->g_done->ea || !globle->g_done->c || !globle->g_done->f)
			{
				write(2, "error info of map not complete\n", 31);
				exit(1);
			}
			globle->g_map->map = parsing_map(line, globle->g_map->map);
		}
		free(line);
	}
	globle->g_map->map_x = len_map_x(globle->g_map->map);
	globle->g_map->map_y = len_map_y(globle->g_map->map);
	ft_last_check_map(globle->g_map->map);
	globle->g_map->map = make_map_same_size(globle->g_map->map, globle->g_map->map_x, globle->g_map->map_y);
	return (globle->g_map);
}

  