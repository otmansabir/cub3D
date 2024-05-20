/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:01:56 by osabir            #+#    #+#             */
/*   Updated: 2024/03/11 15:52:29 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calc_left_ro(t_globel **globel)
{
	double	x;
	double	y;

	if (!globel || !(*globel))
		return ;
	x = (*globel)->g_player->pos_x
		+ cos(((*globel)->g_player->rotation_angle + (M_PI / 2))) * 40;
	y = (*globel)->g_player->pos_y
		+ sin(((*globel)->g_player->rotation_angle + (M_PI / 2))) * 40;
	if (!not_walls(globel, x, y))
	{
		(*globel)->g_player->pos_x = x;
		(*globel)->g_player->pos_y = y;
		(*globel)->event->draws = true;
	}
}

void	calc_right_ro(t_globel **globel)
{
	double	x;
	double	y;

	if (!globel || !(*globel))
		return ;
	x = (*globel)->g_player->pos_x \
		- cos(((*globel)->g_player->rotation_angle \
		+ (M_PI / 2))) * 40;
	y = (*globel)->g_player->pos_y \
		- sin(((*globel)->g_player->rotation_angle \
		+ (M_PI / 2))) * 40;
	if (!not_walls(globel, x, y))
	{
		(*globel)->g_player->pos_x = x;
		(*globel)->g_player->pos_y = y;
		(*globel)->event->draws = true;
	}
}

void	calc_down(t_globel **globel)
{
	double		x;
	double		y;

	if (!globel || !(*globel))
		return ;
	x = (*globel)->g_player->pos_x
		- cos((*globel)->g_player->rotation_angle) * MOVE_SPEED;
	y = (*globel)->g_player->pos_y
		- sin((*globel)->g_player->rotation_angle) * MOVE_SPEED;
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

void	calc_right(t_globel **globel)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->g_player->rotation_angle
		+= (*globel)->g_player->rotation_speed;
	(*globel)->event->draws = true;
}

void	calc_left(t_globel **globel)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->g_player->rotation_angle
		-= (*globel)->g_player->rotation_speed;
	(*globel)->event->draws = true;
}
