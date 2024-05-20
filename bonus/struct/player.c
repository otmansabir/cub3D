/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:55:41 by osabir            #+#    #+#             */
/*   Updated: 2024/04/07 14:03:01 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	rotation_angle(int c)
{
	double	rot_ang;

	rot_ang = 0.0;
	if (c == 'S')
		rot_ang = (M_PI / 2);
	else if (c == 'W')
		rot_ang = M_PI;
	else if (c == 'E')
		rot_ang = 0.0;
	else if (c == 'N')
		rot_ang = ((M_PI * 3) / 2);
	return (rot_ang);
}

void	set_plyr(t_globel **globel, int x, int y)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->g_player->rotation_angle = rotation_angle
		((*globel)->g_map->map[y][x]);
	(*globel)->g_player->pos_x = (x + 0.5) * CUB_SIZE;
	(*globel)->g_player->pos_y = (y + 0.5) * CUB_SIZE;
	(*globel)->g_player->rotation_speed = ROTA_ANGLE * (M_PI / 180);
	(*globel)->g_player->move_speed = MOVE_SPEED;
	(*globel)->g_player->fov_angle = ANGLE * (M_PI / 180);
	(*globel)->g_player->num_rays
		= X_WIDTH / WALL_STRPI_WIDTH;
}

void	ft_player(t_globel **globel)
{
	int	x;
	int	y;

	y = 0;
	if (!globel || !(*globel) || !(*globel)->g_map->map)
		ft_exit_error("Error Empty map\n", globel);
	while ((*globel)->g_map->map[y])
	{
		x = 0;
		while ((*globel)->g_map->map[y][x])
		{
			if (ft_strchr("SWEN", (*globel)->g_map->map[y][x]))
			{
				set_plyr(globel, x, y);
				break ;
			}
			x++;
		}
		y++;
	}
}

t_player	*ft_player_malloc(t_globel **globel)
{
	t_player	*player;

	player = NULL;
	player = malloc(sizeof(t_player));
	if (!player)
		ft_exit_error("Error malloc faild\n", globel);
	player->pos_x = 0;
	player->pos_y = 0;
	player->line_x = 0;
	player->line_y = 0;
	player->derction = 0;
	player->rotation_speed = 0;
	player->rotation_angle = 0;
	player->move_speed = 0;
	player->fov_angle = 0;
	player->num_rays = 0;
	return (player);
}
