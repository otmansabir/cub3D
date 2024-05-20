/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:58:58 by osabir            #+#    #+#             */
/*   Updated: 2024/03/10 16:17:35 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_release(int key, t_globel **globel)
{
	if (!globel || !(*globel))
		return (0);
	if (key == UP || key == KEY_W)
		(*globel)->event->key_front = false;
	if (key == KEY_A)
		(*globel)->event->key_right_ro = false;
	if (key == KEY_D)
		(*globel)->event->key_left_ro = false;
	if (key == DOWN || key == KEY_S)
		(*globel)->event->key_back = false;
	if (key == RIGHT)
		(*globel)->event->key_right = false;
	if (key == LEFT)
		(*globel)->event->key_left = false;
	return (0);
}

int	key_press(int key, t_globel **globel)
{
	if (!globel || !(*globel))
		return (0);
	if (key == UP || key == KEY_W)
		(*globel)->event->key_front = true;
	if (key == DOWN || key == KEY_S)
		(*globel)->event->key_back = true;
	if (key == RIGHT)
		(*globel)->event->key_right = true;
	if (key == KEY_A)
		(*globel)->event->key_right_ro = true;
	if (key == KEY_D)
		(*globel)->event->key_left_ro = true;
	if (key == LEFT)
		(*globel)->event->key_left = true;
	if (key == KEY_O)
		(*globel)->event->key_mouse = true;
	if (key == KEY_K)
		(*globel)->event->key_mouse = false;
	if (key == KEY_C)
		(*globel)->event->mini_map = true;
	if (key == KEY_V)
		(*globel)->event->mini_map = false;
	if (key == ESC)
		ft_esc(globel);
	return (0);
}

int	draw_win(t_globel **globel)
{
	if (!globel || !(*globel))
		return (0);
	if ((*globel)->event->key_left_ro)
		calc_left_ro(globel);
	if ((*globel)->event->key_right_ro)
		calc_right_ro(globel);
	if ((*globel)->event->key_front)
		calc_up(globel);
	if ((*globel)->event->key_back)
		calc_down(globel);
	if ((*globel)->event->key_right)
		calc_right(globel);
	if ((*globel)->event->key_left)
		calc_left(globel);
	if ((*globel)->event->mini_map)
		draw_minimap(globel);
	if ((*globel)->event->draws || !(*globel)->event->mini_map)
		ft_draw(globel);
	return (0);
}

void	make_image(t_globel **globel)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->ea->img
		= mlx_xpm_file_to_image((*globel)->mlx->mlx_ptr,
			(*globel)->g_map->ea, &(*globel)->ea->img_width,
			&(*globel)->ea->img_height);
	if (!(*globel)->ea->img)
		ft_exit_error("Error fiald open xpm\n", globel);
	(*globel)->no->img_addr
		= mlx_get_data_addr((*globel)->no->img,
			&(*globel)->no->bpp, &(*globel)->no->size_line,
			&(*globel)->no->endian);
	(*globel)->so->img_addr
		= mlx_get_data_addr((*globel)->so->img,
			&(*globel)->so->bpp, &(*globel)->so->size_line,
			&(*globel)->so->endian);
	(*globel)->we->img_addr
		= mlx_get_data_addr((*globel)->we->img,
			&(*globel)->we->bpp, &(*globel)->we->size_line,
			&(*globel)->we->endian);
	(*globel)->ea->img_addr
		= mlx_get_data_addr((*globel)->ea->img,
			&(*globel)->ea->bpp, &(*globel)->ea->size_line,
			&(*globel)->ea->endian);
}

void	ft_get_img_xpm(t_globel **globel)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->no->img
		= mlx_xpm_file_to_image((*globel)->mlx->mlx_ptr,
			(*globel)->g_map->no, &(*globel)->no->img_width,
			&(*globel)->no->img_height);
	if (!(*globel)->no->img)
		ft_exit_error("Error fiald open xpm\n", globel);
	(*globel)->so->img
		= mlx_xpm_file_to_image((*globel)->mlx->mlx_ptr,
			(*globel)->g_map->so, &(*globel)->so->img_width,
			&(*globel)->so->img_height);
	if (!(*globel)->so->img)
		ft_exit_error("Error fiald open xpm\n", globel);
	(*globel)->we->img
		= mlx_xpm_file_to_image((*globel)->mlx->mlx_ptr,
			(*globel)->g_map->we, &(*globel)->we->img_width,
			&(*globel)->we->img_height);
	if (!(*globel)->we->img)
		ft_exit_error("Error fiald open xpm\n", globel);
	make_image(globel);
}
