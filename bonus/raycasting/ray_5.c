/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:45:26 by osabir            #+#    #+#             */
/*   Updated: 2024/03/14 14:09:43 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_image(t_globel **globel)
{
	if (!globel || !(*globel))
		return ;
	mlx_put_image_to_window((*globel)->mlx->mlx_ptr,
		(*globel)->mlx->mlx_window, (*globel)->mlx->img_ptr, 0, 0);
}

t_xpm	*image(t_globel **globel, double rayangle)
{
	t_xpm	*x;

	if (!globel || !(*globel))
		return (NULL);
	if ((*globel)->cast->its_hit_vertical)
	{
		if (rayangle > (M_PI / 2) && rayangle < ((3 * M_PI) / 2))
			x = (*globel)->we;
		else
			x = (*globel)->ea;
	}
	else
	{
		if (rayangle > 0 && rayangle < M_PI)
			x = (*globel)->so;
		else
			x = (*globel)->no;
	}
	return (x);
}

void	calc_image(t_globel **globel, t_xpm **images)
{
	if (!globel || !(*globel))
		return ;
	if ((*globel)->cast->its_hit_vertical)
		(*globel)->texture->offset_x
			= (int)(*globel)->cast->wall_hit_y % CUB_SIZE;
	else
		(*globel)->texture->offset_x
			= (int)(*globel)->cast->wall_hit_x % CUB_SIZE;
	(*globel)->texture->factor = (*images)->img_width / CUB_SIZE;
	(*globel)->texture->offset_x *= (*globel)->texture->factor;
	(*globel)->texture->img_data = (unsigned int *)(*images)->img_addr;
}

void	calc_top_botton(t_globel **globel
		, double rayangle, int *top, int *bottom)
{
	if (!globel || !(*globel))
		return ;
	(*top) = 0;
	(*bottom) = 0;
	(*globel)->texture->ray_distance = (*globel)->cast->distance
		* cos(rayangle - (*globel)->g_player->rotation_angle);
	(*globel)->texture->distance_p = ((double)((X_WIDTH) / 2))
		/ tan((*globel)->g_player->fov_angle / 2);
	(*globel)->texture->wall_strip_height
		= ((double)(CUB_SIZE / (*globel)->texture->ray_distance))
		* (*globel)->texture->distance_p;
	(*top) = ((double)(Y_HEIGHT) / 2)
		- (double)((*globel)->texture->wall_strip_height / 2);
	(*bottom) = ((double)(*globel)->texture->wall_strip_height / 2)
		+ ((double)(Y_HEIGHT) / 2);
}

void	render_3d_projecte_walls(t_globel **globel, int column, double rayangle)
{
	int		top;
	int		bottom;
	t_xpm	*images;
	int		i;

	i = 0;
	if (!globel || !(*globel))
		return ;
	calc_top_botton(globel, rayangle, &top, &bottom);
	images = image(globel, rayangle);
	calc_image(globel, &images);
	while (i < top)
		my_put_pixel(globel, column, i++, (*globel)->g_map->c);
	while (i < bottom && i < Y_HEIGHT)
	{
		(*globel)->texture->offset_y = (i - top) * ((double)images->img_height
				/ (*globel)->texture->wall_strip_height);
		my_put_pixel(globel, column, i++,
			(*globel)->texture->img_data[(images->img_width \
			* (*globel)->texture->offset_y) + (*globel)->texture-> offset_x]);
	}
	while (i < Y_HEIGHT)
		my_put_pixel(globel, column, i++, (*globel)->g_map->f);
}
