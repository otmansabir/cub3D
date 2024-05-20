/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:03:24 by osabir            #+#    #+#             */
/*   Updated: 2024/03/11 15:50:22 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	not_wall(t_globel **globel, double lx, double ly)
{
	int	x;
	int	y;

	if (!globel || !(*globel))
		return (false);
	x = floor((lx) / CUB_SIZE);
	y = floor((ly) / CUB_SIZE);
	if (y < 0 || y >= (*globel)->g_map->map_y
		|| x < 0 || x >= (*globel)->g_map->map_x)
		return (true);
	if ((*globel)->g_map->map[y][x] == '1')
		return (true);
	return (false);
}

bool	not_walls(t_globel **globel, double lx, double ly)
{
	if (!globel || !(*globel))
		return (false);
	if ((int)(ly / CUB_SIZE) < 0
		|| (int)(ly / CUB_SIZE) >= (*globel)->g_map->map_y
		|| (int)(lx / CUB_SIZE) < 0
		|| (int)(lx / CUB_SIZE) >= (*globel)->g_map->map_x)
		return (true);
	if ((*globel)->g_map->map[(int)(ly)
		/ CUB_SIZE][(int)(lx) / CUB_SIZE] == '1'
		|| (*globel)->g_map->map[(int)(ly + 2)
		/ CUB_SIZE][(int)(lx) / CUB_SIZE] == '1'
		|| (*globel)->g_map->map[(int)(ly - 2)
		/ CUB_SIZE][(int)(lx) / CUB_SIZE] == '1'
		|| (*globel)->g_map->map[(int)(ly)
		/ CUB_SIZE][(int)(lx + 2) / CUB_SIZE] == '1'
		|| (*globel)->g_map->map[(int)(ly)
		/ CUB_SIZE][(int)(lx - 2) / CUB_SIZE] == '1'
		|| (*globel)->g_map->map[(int)(ly + 2)
		/ CUB_SIZE][(int)(lx + 2) / CUB_SIZE] == '1'
		|| (*globel)->g_map->map[(int)(ly - 2)
		/ CUB_SIZE][(int)(lx - 2) / CUB_SIZE] == '1')
		return (true);
	return (false);
}

void	calc_up(t_globel **globel)
{
	double		x;
	double		y;

	if (!globel || !(*globel))
		return ;
	x = (*globel)->g_player->pos_x
		+ cos((*globel)->g_player->rotation_angle) * MOVE_SPEED;
	y = (*globel)->g_player->pos_y
		+ sin((*globel)->g_player->rotation_angle) * MOVE_SPEED;
	if ((not_walls(globel, (*globel)->g_player->pos_x, y)
			&& not_walls(globel, x, (*globel)->g_player->pos_y)))
		return ;
	if (!not_walls(globel, x, y))
	{
		(*globel)->g_player->pos_x = x;
		(*globel)->g_player->pos_y = y;
		(*globel)->event->draws = true;
	}
}

void	ft_draw(t_globel **globel)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->event->draws = false;
	mlx_destroy_image((*globel)->mlx->mlx_ptr, (*globel)->mlx->img_ptr);
	mlx_clear_window((*globel)->mlx->mlx_ptr, (*globel)->mlx->mlx_window);
	(*globel)->mlx->img_ptr
		= mlx_new_image((*globel)->mlx->mlx_ptr, X_WIDTH, Y_HEIGHT);
	(*globel)->mlx->buffer
		= mlx_get_data_addr((*globel)->mlx->img_ptr,
			&(*globel)->mlx->bpp, &(*globel)->mlx->size_line,
			&(*globel)->mlx->endian);
	draw_window(globel);
}
