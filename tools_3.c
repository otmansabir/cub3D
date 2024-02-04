/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:05:57 by osabir            #+#    #+#             */
/*   Updated: 2024/02/04 14:05:58 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	checkside2(char *line)
{
	int		i;

	i = 1;
	ft_test_forma(line);
	while (ft_strchr(" \t\v\r\f", line[i]))
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (ft_isdigit(line[i]))
		{
			while (line[i] && line[i] != '\n')
			{
				if ((ft_strchr(", \t\v\r\f", line[i])) || line[i] == '\0')
					break ;
				else
					i++;
			}
			if (line[i] && line[i] != ',' && ft_strchr(" \t\v\r\f", line[i]))
			{
				while (ft_strchr(" \t\v\r\f", line[i]))
					i++;
				if (ft_isdigit(line[i]))
				{
					write(2, "not corric forma\n", 17);
					exit(1);
				}
			}
		}
		else
			i++;
	}
	return (color_nbr(line));
}

char	*get_line(int fd)
{
	char		*line;
	static int	get;

	line = get_next_line(fd);
	if (!get && !line)
	{
		write(2, "empty file", 10);
		exit (1);
	}
	get = 1;
	return (line);
}

