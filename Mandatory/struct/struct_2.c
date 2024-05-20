/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:08:24 by osabir            #+#    #+#             */
/*   Updated: 2024/03/11 17:43:31 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_key_event	*make_null(t_globel **globel)
{
	t_key_event	*event;

	event = malloc(sizeof(t_key_event));
	if (!event)
		ft_exit_error("Error malloc faild\n", globel);
	event->key_front = false;
	event->key_left_ro = false;
	event->key_right_ro = false;
	event->key_back = false;
	event->key_right = false;
	event->key_left = false;
	event->draws = true;
	return (event);
}

t_horizontal	*aloc_horzi(t_globel **globel)
{
	t_horizontal	*x;

	x = NULL;
	x = malloc(sizeof(t_horizontal));
	if (!x)
		ft_exit_error("Error malloc faild\n", globel);
	x->x_intercept = 0;
	x->y_intercept = 0;
	x->x_step = 0;
	x->y_step = 0;
	x->found_horiz_x = 0;
	x->found_horiz_y = 0;
	x->found_horiz_wall_hit = 0;
	return (x);
}

t_vertical	*aloc_vert(t_globel **globel)
{
	t_vertical	*x;

	x = NULL;
	x = malloc(sizeof(t_vertical));
	if (!x)
		ft_exit_error("Error malloc faild\n", globel);
	x->x_intercept = 0;
	x->y_intercept = 0;
	x->x_step = 0;
	x->y_step = 0;
	x->found_vertic_x = 0;
	x->found_vertic_y = 0;
	x->found_vertic_wall_hit = 0;
	return (x);
}

t_mlx	*mlx_aloc(t_globel **globel)
{
	t_mlx	*mlx;

	mlx = NULL;
	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		ft_exit_error("Error malloc faild\n", globel);
	mlx->mlx_ptr = NULL;
	mlx->mlx_window = NULL;
	mlx->img_ptr = NULL;
	mlx->buffer = NULL;
	mlx->bpp = 0;
	mlx->size_line = 0;
	mlx->endian = 0;
	return (mlx);
}
