/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:37:05 by osabir            #+#    #+#             */
/*   Updated: 2024/05/06 18:51:21 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	where_i_looking_to(t_globel **globel, double rayangle)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->cast->ray_facing_up = false;
	(*globel)->cast->ray_facing_down = false;
	(*globel)->cast->ray_facing_right = false;
	(*globel)->cast->ray_facing_left = false;
	if (rayangle > 0 && rayangle < M_PI)
		(*globel)->cast->ray_facing_down = true;
	if (!(*globel)->cast->ray_facing_down)
		(*globel)->cast->ray_facing_up = true;
	if (rayangle < 0.5 * M_PI || rayangle > 1.5 * M_PI)
		(*globel)->cast->ray_facing_right = true;
	if (!(*globel)->cast->ray_facing_right)
		(*globel)->cast->ray_facing_left = true;
}

double	normlize_angle(double rayangle)
{
	rayangle = fmod(rayangle, (2 * M_PI));
	if (rayangle < 0)
		rayangle += 2 * M_PI;
	return (rayangle);
}

void	ray_casting(t_globel **globel, double rayangle, int column)
{
	if (!globel || !(*globel))
		return ;
	rayangle = normlize_angle(rayangle);
	where_i_looking_to(globel, rayangle);
	horiz(globel, rayangle);
	vertic(globel, rayangle);
	calc_horiz_vertic(globel);
	render_3d_projecte_walls(globel, column, rayangle);
}

void	draw_ray(t_globel **globel)
{
	int		column;
	double	rayangle;

	column = 0;
	if (!globel || !(*globel))
		return ;
	rayangle = (*globel)->g_player->rotation_angle - ((*globel)->g_player->fov_angle / 2);
	while (column < (*globel)->g_player->num_rays)
	{
		ray_casting(globel, rayangle, column);
		rayangle += (*globel)->g_player->fov_angle / (*globel)->g_player->num_rays;
		column++;
	}
}

void	draw_window(t_globel **globel)
{
	if (!globel || !(*globel))
		return ;
	draw_ray(globel);
	put_image(globel);
}
