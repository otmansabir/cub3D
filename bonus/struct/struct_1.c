/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:06:44 by osabir            #+#    #+#             */
/*   Updated: 2024/03/10 16:16:29 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_mouse	*mouse_var(t_globel **globel)
{
	t_mouse	*mouse;

	mouse = NULL;
	mouse = malloc(sizeof(t_mouse));
	if (!mouse)
		ft_exit_error("Error malloc faild\n", globel);
	mouse->old_x = 0;
	mouse->old_y = 0;
	return (mouse);
}

t_xpm	*aloc_xpm(t_globel **globel)
{
	t_xpm	*x;

	x = NULL;
	x = malloc(sizeof(t_xpm));
	if (!x)
		ft_exit_error("Error malloc faild\n", globel);
	x->img = NULL;
	x->img_addr = NULL;
	x->img_width = 0;
	x->img_height = 0;
	x->bpp = 0;
	x->size_line = 0;
	x->endian = 0;
	return (x);
}

t_cast	*aloc_cast(t_globel **globel)
{
	t_cast	*cast;

	cast = NULL;
	cast = malloc(sizeof(t_cast));
	if (!cast)
		ft_exit_error("Error malloc faild\n", globel);
	cast->horizontal = aloc_horzi(globel);
	cast->vertical = aloc_vert(globel);
	cast->wall_hit_x = 0;
	cast->wall_hit_y = 0;
	cast->distance = 0;
	cast->ray_facing_down = 0;
	cast->ray_facing_up = 0;
	cast->ray_facing_right = 0;
	cast->ray_facing_left = 0;
	cast->its_hit_vertical = 0;
	return (cast);
}

t_texture	*aloc_texture(t_globel **globel)
{
	t_texture	*x;

	x = NULL;
	x = malloc(sizeof(t_texture));
	if (!x)
		ft_exit_error("Error malloc faild\n", globel);
	x->distance_p = 0;
	x->factor = 0;
	x->img_data = 0;
	x->offset_x = 0;
	x->offset_y = 0;
	x->ray_distance = 0;
	x->wall_strip_height = 0;
	return (x);
}

t_globel	*everthing(t_globel *globel)
{
	globel = malloc(sizeof(t_globel));
	if (!globel)
		ft_exit_error("Error malloc faild\n", NULL);
	globel->g_map = ft_malloc(&globel);
	globel->g_player = ft_player_malloc(&globel);
	globel->g_done = give_value(&globel);
	globel->event = make_null(&globel);
	globel->mlx = mlx_aloc(&globel);
	globel->mouse = mouse_var(&globel);
	globel->no = aloc_xpm(&globel);
	globel->so = aloc_xpm(&globel);
	globel->we = aloc_xpm(&globel);
	globel->ea = aloc_xpm(&globel);
	globel->cast = aloc_cast(&globel);
	globel->texture = aloc_texture(&globel);
	return (globel);
}
