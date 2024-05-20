/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:47:44 by osabir            #+#    #+#             */
/*   Updated: 2024/04/29 13:37:26 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

typedef struct s_v
{
	double	x;
	double	y;
	double	px;
	double	py;
	int		line;
}			t_v;

void	draw_line(t_globel **globel, int color)
{
	t_v		v;
	int		dx;
	int		dy;
	int		line;

	if (!globel || !(*globel))
		return ;
	dx = (*globel)->g_player->line_x - 100;
	dy = (*globel)->g_player->line_y - 100;
	if (abs(dx) > abs(dy))
		line = abs(dx);
	else
		line = abs(dy);
	v.x = (double)dx / (double)line;
	v.y = (double)dy / (double)line;
	v.px = 100;
	v.py = 100;
	while (line--)
	{
		my_put_pixel(globel, ((int)v.px), ((int)v.py), color);
		v.px += v.x;
		v.py += v.y;
	}
}

void	draw_circle(t_globel **globel, int color)
{
	int	i;
	int	j;

	if (!globel || !(*globel))
		return ;
	j = 100 - 4;
	while (j < 100 + 4)
	{
		i = 100 - 4;
		while (i < 100 + 4)
		{
			my_put_pixel(globel, i, j, color);
			i++;
		}
		j++;
	}
}

void	calc_minimap(t_globel **globel)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->g_player->mini_x = (*globel)->g_player->pos_x / CUB_SIZE;
	(*globel)->g_player->mini_y = (*globel)->g_player->pos_y / CUB_SIZE;
	(*globel)->g_player->mini_x *= MINI_CUB;
	(*globel)->g_player->mini_y *= MINI_CUB;
	(*globel)->g_player->x_ply = (*globel)->g_player->mini_x - 100;
	(*globel)->g_player->y_ply = (*globel)->g_player->mini_y - 100;
}

void	calc_line(t_globel **globel, int color)
{
	if (!globel || !(*globel))
		return ;
	(*globel)->g_player->line_x = 100;
	(*globel)->g_player->line_y = 100;
	(*globel)->g_player->line_x += cos((*globel)->g_player->rotation_angle) * LINE_LENGTH;
	(*globel)->g_player->line_y += sin((*globel)->g_player->rotation_angle) * LINE_LENGTH;
	draw_line(globel, color);
}

void	draw_minimap(t_globel **globel)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!globel || !(*globel))
		return ;
	calc_minimap(globel);
	while ((*globel)->event->mini_map && j < 200)
	{
		i = 0;
		while (i < 200)
		{
			if (not_wall1(globel, ((*globel)->g_player->x_ply + i),
					((*globel)->g_player->y_ply + j)))
				my_put_pixel(globel, i, j, BLACK);
			else
				my_put_pixel(globel, i, j, WHITE);
			i++;
		}
		j++;
	}
	draw_circle(globel, RED);
	calc_line(globel, ORANGE);
	put_image(globel);
}
