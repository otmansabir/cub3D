/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:40:56 by osabir            #+#    #+#             */
/*   Updated: 2024/05/05 16:22:24 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_val(t_globel **globel, double x, double y)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->cast->horizontal->found_horiz_wall_hit = true;
	(*globel)->cast->horizontal->found_horiz_x = x;
	(*globel)->cast->horizontal->found_horiz_y = y;
}

void	clac_horiz(t_globel **globel, double rayangle)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->cast->horizontal->found_horiz_wall_hit = false;
	(*globel)->cast->horizontal->y_intercept = floor((*globel)->g_player->pos_y / CUB_SIZE) * CUB_SIZE;
	if ((*globel)->cast->ray_facing_down)
		(*globel)->cast->horizontal->y_intercept += CUB_SIZE;
		
	(*globel)->cast->horizontal->x_intercept = (*globel)->g_player->pos_x + ((*globel)->cast->horizontal->y_intercept - (*globel)->g_player->pos_y) / tan(rayangle);
	
	(*globel)->cast->horizontal->y_step = CUB_SIZE;
	if ((*globel)->cast->ray_facing_up)
		(*globel)->cast->horizontal->y_step *= -1;
		
	(*globel)->cast->horizontal->x_step = CUB_SIZE / tan(rayangle);
	if ((*globel)->cast->ray_facing_left
		&& (*globel)->cast->horizontal->x_step > 0)
		(*globel)->cast->horizontal->x_step *= -1;
	if ((*globel)->cast->ray_facing_right
		&& (*globel)->cast->horizontal->x_step < 0)
		(*globel)->cast->horizontal->x_step *= -1;
}

void	horiz(t_globel **globel, double rayangle)
{
	double	next_horiz_x;
	double	next_horiz_y;

	if (!globel || !(*globel))
		return ;
	clac_horiz(globel, rayangle);
	next_horiz_x = (*globel)->cast->horizontal->x_intercept;
	next_horiz_y = (*globel)->cast->horizontal->y_intercept;
	while (next_horiz_x >= 0 && next_horiz_x
		<= (*globel)->g_map->map_x * CUB_SIZE
		&& next_horiz_y >= 0 && next_horiz_y
		<= (*globel)->g_map->map_y * CUB_SIZE)
	{
		if (not_wall(globel, next_horiz_x,
				next_horiz_y - (*globel)->cast->ray_facing_up))
		{
			set_val(globel, next_horiz_x, next_horiz_y);
			return ;
		}
		next_horiz_x += (*globel)->cast->horizontal->x_step;
		next_horiz_y += (*globel)->cast->horizontal->y_step;
	}
	(*globel)->cast->horizontal->found_horiz_x = LONG_MAX;
	(*globel)->cast->horizontal->found_horiz_y = LONG_MAX;
}
