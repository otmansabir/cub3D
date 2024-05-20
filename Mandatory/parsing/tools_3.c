/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 14:05:57 by osabir            #+#    #+#             */
/*   Updated: 2024/03/10 16:15:13 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_correctt_digit(char *line, t_globel **globel)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!line || !globel)
		return ;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] && line[i] != '\n' && !ft_isdigit(line[i]))
			i++;
		if (ft_isdigit(line[i]))
			j++;
		while (line[i] && line[i] != '\n' && ft_isdigit(line[i]))
			i++;
	}
	if (j != 3)
		ft_exit_error("Error Not a correct format\n", globel);
}

void	checkside22(char *line, int *i, t_globel **globel)
{
	if (!line || !globel)
		return ;
	while (line[*i] && line[*i] != '\n')
	{
		if ((ft_strchr(", \t\v\r\f", line[*i])) || line[*i] == '\0')
			break ;
		else
			(*i)++;
	}
	if (line[*i] && line[*i] != ',' && ft_strchr(" \t\v\r\f", line[*i]))
	{
		while (line[*i] && ft_strchr(" \t\v\r\f", line[*i]))
			(*i)++;
		if (ft_isdigit(line[*i]))
			ft_exit_error("Error Not a correct format\n", globel);
	}
}

int	checkside2(char *line, t_globel **globel)
{
	int		i;

	i = 1;
	if (!line || !globel)
		return (0);
	ft_correctt_digit(line, globel);
	ft_test_forma(line, globel);
	while (ft_strchr(" \t\v\r\f", line[i]))
		i++;
	while (line[i] && line[i] != '\n')
	{
		if (ft_isdigit(line[i]))
			checkside22(line, &i, globel);
		else
			i++;
	}
	return (color_nbr(line, globel));
}

char	*get_line(int fd, t_globel **globel)
{
	char		*line;
	static int	get;

	if (!globel)
		return (NULL);
	line = get_next_line(fd);
	if (!get && !line)
		ft_exit_error("Error empty file", globel);
	get = 1;
	return (line);
}
