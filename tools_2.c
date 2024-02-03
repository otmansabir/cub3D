#include "cub3d.h"

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

char	*check_side(char *line)
{
	char	*tmp;
	int		i;

	i = 2;
	while (ft_strchr(" \t\v\r\f", line[i]))
		i++;
	tmp = ft_strdup("");
	while (line[i] != '\n' && line[i] != '\0')
	{
		tmp = ft_charjoin(tmp, line[i]);
		i++;
	}
	if (open(tmp, O_RDONLY) == -1)
	{
		perror("open file xpm");
		exit(1);
	}
	return (tmp);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_test_forma(char *line)
{
	int	i;
	int	colon;

	i = 1;
	colon = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_isdigit(line[i]) && !ft_strchr(", \t\v\r\f", line[i]))
		{
			write(2, "not corric forma\n", 17);
			exit(1);
		}
		if (line[i] == ',')
			colon++;
		i++;
	}
	if (colon != 2)
	{
		write(2, "not corric forma\n", 17);
		exit(1);
	}
}


int	color_nbr(char *line)
{
	t_color	color;
	char	**split;
	char	*copy;


	copy = line;
	copy++;
	split = ft_split(copy, ',');
	color.red = ft_atoi(split[0]);
	if (color.red > 255)
	{
		write(2, "color > 255\n", 12);
		exit(1);
	}
	color.green = ft_atoi(split[1]);
	if (color.green > 255)
	{
		write(2, "color > 255\n", 12);
		exit(1);
	}
	color.blue = ft_atoi(split[2]);
	if (color.blue > 255)
	{
		write(2, "color > 255\n", 12);
		exit(1);
	}
	return ((color.red << 16) | (color.green << 8) | color.blue);
}
