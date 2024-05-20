/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:42:17 by osabir            #+#    #+#             */
/*   Updated: 2024/05/06 19:00:05 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_val_v(t_globel **globel, double x, double y)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->cast->vertical->found_vertic_wall_hit = true;
	(*globel)->cast->vertical->found_vertic_x = x;
	(*globel)->cast->vertical->found_vertic_y = y;
}

void	calc_vert(t_globel **globel, double rayangle)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->cast->vertical->found_vertic_wall_hit = false;

	(*globel)->cast->vertical->x_intercept = floor((*globel)->g_player->pos_x / CUB_SIZE) * CUB_SIZE;
	if ((*globel)->cast->ray_facing_right)
		(*globel)->cast->vertical->x_intercept += CUB_SIZE;
		
	(*globel)->cast->vertical->y_intercept = (*globel)->g_player->pos_y + ((*globel)->cast->vertical->x_intercept - (*globel)->g_player->pos_x) * tan(rayangle);
	
	(*globel)->cast->vertical->x_step = CUB_SIZE;
	if ((*globel)->cast->ray_facing_left)
		(*globel)->cast->vertical->x_step *= -1;
		
	(*globel)->cast->vertical->y_step = CUB_SIZE * tan(rayangle);
	
	if ((*globel)->cast->ray_facing_up
		&& (*globel)->cast->vertical->y_step > 0)
		(*globel)->cast->vertical->y_step *= -1;
		
	if ((*globel)->cast->ray_facing_down
		&& (*globel)->cast->vertical->y_step < 0)
		(*globel)->cast->vertical->y_step *= -1;
}

void	vertic(t_globel **globel, double rayangle)
{
	double	next_vertic_x;
	double	next_vertic_y;

	if (!globel || !(*globel))
		return ;
	calc_vert(globel, rayangle);
	next_vertic_x = (*globel)->cast->vertical->x_intercept;
	next_vertic_y = (*globel)->cast->vertical->y_intercept;
	while (next_vertic_x >= 0 && next_vertic_x
		<= (*globel)->g_map->map_x * CUB_SIZE
		&& next_vertic_y >= 0 && next_vertic_y
		<= (*globel)->g_map->map_y * CUB_SIZE)
	{
		if (not_wall(globel, next_vertic_x - (*globel)->cast->ray_facing_left, next_vertic_y))
		{
			set_val_v(globel, next_vertic_x, next_vertic_y);
			return ;
		}
		next_vertic_x += (*globel)->cast->vertical->x_step;
		next_vertic_y += (*globel)->cast->vertical->y_step;
	}
	(*globel)->cast->vertical->found_vertic_x = LONG_MAX;
	(*globel)->cast->vertical->found_vertic_y = LONG_MAX;
}
