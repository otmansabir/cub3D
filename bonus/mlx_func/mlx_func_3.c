/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_func_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:09:51 by osabir            #+#    #+#             */
/*   Updated: 2024/03/11 10:36:26 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_free_sturct1(t_globel **globel, int i)
{
	if ((*globel)->mlx && i == 1)
	{
		mlx_destroy_image((*globel)->mlx->mlx_ptr, (*globel)->mlx->img_ptr);
		mlx_clear_window((*globel)->mlx->mlx_ptr, (*globel)->mlx->mlx_window);
		mlx_destroy_window((*globel)->mlx->mlx_ptr, (*globel)->mlx->mlx_window);
	}
	if ((*globel)->mlx)
		free((*globel)->mlx);
	if ((*globel)->g_player)
		free((*globel)->g_player);
	if ((*globel)->g_done)
		free((*globel)->g_done);
	if ((*globel)->cast)
	{
		if ((*globel)->cast->horizontal)
			free((*globel)->cast->horizontal);
		if ((*globel)->cast->vertical)
			free((*globel)->cast->vertical);
		free((*globel)->cast);
	}
}

void	ft_free_sturct2(t_globel **globel)
{
	int	i;

	i = 0;
	if ((*globel)->g_map)
	{
		if ((*globel)->g_map->ea)
			free((*globel)->g_map->ea);
		if ((*globel)->g_map->no)
			free((*globel)->g_map->no);
		if ((*globel)->g_map->so)
			free((*globel)->g_map->so);
		if ((*globel)->g_map->we)
			free((*globel)->g_map->we);
		if ((*globel)->g_map->map)
		{
			while ((*globel)->g_map->map[i])
				free((*globel)->g_map->map[i++]);
			free((*globel)->g_map->map);
		}
		free((*globel)->g_map);
	}
	if ((*globel)->event)
		free((*globel)->event);
	if ((*globel)->mouse)
		free((*globel)->mouse);
}

void	ft_free_sturct3(t_globel **globel)
{
	if ((*globel)->ea)
	{
		if ((*globel)->ea->img)
			free((*globel)->ea->img);
		if ((*globel)->ea->img_addr)
			free((*globel)->ea->img_addr);
		free((*globel)->ea);
	}
	if ((*globel)->we)
	{
		if ((*globel)->we->img)
			free((*globel)->we->img);
		if ((*globel)->we->img_addr)
			free((*globel)->we->img_addr);
		free((*globel)->we);
	}
	if ((*globel)->no)
	{
		if ((*globel)->no->img)
			free((*globel)->no->img);
		if ((*globel)->no->img_addr)
			free((*globel)->no->img_addr);
		free((*globel)->no);
	}
}

void	ft_free_sturct4(t_globel **globel)
{
	if ((*globel)->so)
	{
		if ((*globel)->so->img)
			free((*globel)->so->img);
		if ((*globel)->so->img_addr)
			free((*globel)->so->img_addr);
		free((*globel)->so);
	}
	if ((*globel)->texture)
		free((*globel)->texture);
	if (*globel)
		free(*globel);
}

int	mouse_move(int x, int y, t_globel **globel)
{
	if (!globel || !(*globel))
		return (0);
	if (x < 0 || x > X_WIDTH || y < 0
		|| y > Y_HEIGHT || !(*globel)->event->key_mouse)
		return (0);
	if (x < (*globel)->mouse->old_x)
		calc_left(globel);
	if (x > (*globel)->mouse->old_x)
		calc_right(globel);
	(*globel)->mouse->old_x = x;
	(*globel)->mouse->old_y = y;
	return (0);
}
