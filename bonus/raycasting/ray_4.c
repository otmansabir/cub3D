/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:44:05 by osabir            #+#    #+#             */
/*   Updated: 2024/02/21 17:44:53 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	ft_clalc_ver_hor(t_globel **globel, double *h, double *v)
{
	if (!globel || !(*globel))
		return ;
	if ((*globel)->cast->horizontal->found_horiz_wall_hit)
		(*h) = distance((*globel)->g_player->pos_x,
				(*globel)->g_player->pos_y,
				(*globel)->cast->horizontal->found_horiz_x,
				(*globel)->cast->horizontal->found_horiz_y);
	if (!(*globel)->cast->horizontal->found_horiz_wall_hit)
		(*h) = LONG_MAX;
	if ((*globel)->cast->vertical->found_vertic_wall_hit)
		(*v) = distance((*globel)->g_player->pos_x,
				(*globel)->g_player->pos_y,
				(*globel)->cast->vertical->found_vertic_x,
				(*globel)->cast->vertical->found_vertic_y);
	if (!(*globel)->cast->vertical->found_vertic_wall_hit)
		(*v) = LONG_MAX;
}

void	calc_horiz_vertic(t_globel **globel)
{
	double	horiz_distance;
	double	vertic_distance;

	horiz_distance = 0;
	vertic_distance = 0;
	if (!globel || !(*globel))
		return ;
	ft_clalc_ver_hor(globel, &horiz_distance, &vertic_distance);
	(*globel)->cast->its_hit_vertical = false;
	if (horiz_distance < vertic_distance)
	{
		(*globel)->cast->wall_hit_x
			= (*globel)->cast->horizontal->found_horiz_x;
		(*globel)->cast->wall_hit_y
			= (*globel)->cast->horizontal->found_horiz_y;
		(*globel)->cast->distance = horiz_distance;
	}
	else
	{
		(*globel)->cast->wall_hit_x = (*globel)->cast->vertical->found_vertic_x;
		(*globel)->cast->wall_hit_y = (*globel)->cast->vertical->found_vertic_y;
		(*globel)->cast->distance = vertic_distance;
		(*globel)->cast->its_hit_vertical = true;
	}
}
