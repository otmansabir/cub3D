/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_12.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:53:10 by osabir            #+#    #+#             */
/*   Updated: 2024/04/20 10:37:28 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_put_pixel(t_globel **globel, int x, int y, int color)
{
	char	*offset;

	if (!globel || !(*globel))
		return ;
	offset = (*globel)->mlx->buffer
		+ ((*globel)->mlx->size_line * y) + (x * ((*globel)->mlx->bpp / 8));
	if (x >= 0 && x < X_WIDTH && y >= 0 && y < Y_HEIGHT)
		*(unsigned int *)offset = color;
}

void	ft_exit_error(char *error, t_globel **globel)
{
	ft_putstr_fd(error, 2, globel);
	if (globel)
		ft_globel_free(globel, 0);
	exit(1);
}

void	ft_putstr_fd(char *s, int fd, t_globel **globel)
{
	int	i;

	i = 0;
	if (!s)
		ft_exit_error("Error string is null\n", globel);
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

bool	not_wall1(t_globel **globel, int lx, int ly)
{
	int	x;
	int	y;

	if (!globel || !(*globel))
		return (false);
	x = floor(lx / 16);
	y = floor(ly / 16);
	printf("lx = %i, ly = %i, x = %i, y = %i\n", lx, ly, x, y);
	if (y < 0 || y >= (*globel)->g_map->map_y
		|| x < 0 || x >= (*globel)->g_map->map_x)
		return (false);
	if ((*globel)->g_map->map[y][x] == '1')
		return (true);
	return (false);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
