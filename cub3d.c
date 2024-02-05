/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:23:35 by osabir            #+#    #+#             */
/*   Updated: 2024/02/05 13:00:05 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

void	ft_exit_error(char *error)
{
	ft_putstr_fd(error, 2);
	exit(1);
}

void	check_file_name(char *file_name, char *compre)
{
	int	i;
	int	j;

	i = ft_strlen(file_name);
	j = ft_strlen(compre);
	while (j > 0)
	{
		if (file_name[--i] != compre[--j])
			ft_exit_error("error file name\n");
	}
	if (i > 0)
		return ;
	ft_exit_error("error file name\n");
}

void	ft_draw_pixel(t_mlx **mlx, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < CUB_SIZE - 1)
	{
		i = 0;
		while (i < CUB_SIZE - 1)
		{
			mlx_pixel_put((*mlx)->mlx_ptr,
				(*mlx)->mlx_window, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void draw_circle(t_globel **globel, t_mlx **mlx, int color)
{
	int	i;
	int	j;

	i = (*globel)->g_player->pos_x - RADIUS;
	while (i <= (*globel)->g_player->pos_x + RADIUS)
	{
		j = (*globel)->g_player->pos_y - RADIUS;
		while (j <= (*globel)->g_player->pos_y + RADIUS)
		{
			if ((i - (*globel)->g_player->pos_x)
				* (i - (*globel)->g_player->pos_x)
				+ (j - (*globel)->g_player->pos_y)
				* (j - (*globel)->g_player->pos_y) <= RADIUS * RADIUS)
				mlx_pixel_put((*mlx)->mlx_ptr, (*mlx)->mlx_window, i, j, color);
			j++;
		}
		i++;
	}
}

void draw_line(t_globel **globle, int color)
{
	int		dx;
	int		dy;
	int		line;
	double	x;
	double	y;
	double	px;
	double	py;

	dx = (*globle)->g_player->line_x - (*globle)->g_player->pos_x;
	dy = (*globle)->g_player->line_y - (*globle)->g_player->pos_y;
	if (abs(dx) > abs(dy))
		line = abs(dx);
	else
		line = abs(dy);
	x = (double)dx / (double)line;
	y = (double)dy / (double)line;
	px = (*globle)->g_player->pos_x;
	py = (*globle)->g_player->pos_y;
	while (line--)
	{
		mlx_pixel_put((*globle)->mlx->mlx_ptr, (*globle)->mlx->mlx_window, (int)px, (int)py, color);
		px += x;
		py += y;
	}
}

void	calc_line(t_globel **globle, int color)
{
	(*globle)->g_player->line_x = (*globle)->g_player->pos_x;
	(*globle)->g_player->line_y = (*globle)->g_player->pos_y;
	(*globle)->g_player->line_x
		+= cos((*globle)->g_player->rotation_angle) * LINE_LENGTH;
	(*globle)->g_player->line_y
		+= sin((*globle)->g_player->rotation_angle) * LINE_LENGTH;
	draw_line(globle, color);
}

void	draw_window(t_mlx **mlx, t_globel **globel)
{
	int	x;
	int	y;

	y = 0;
	while ((*globel)->g_map->map[y])
	{
		x = 0;
		while ((*globel)->g_map->map[y][x]) 
		{
			if ((*globel)->g_map->map[y][x] == '1')
				ft_draw_pixel(mlx, x * CUB_SIZE, y * CUB_SIZE, BLACK);
			else if ((*globel)->g_map->map[y][x] == '0'
				|| ft_strchr("SWEN", (*globel)->g_map->map[y][x]))
				ft_draw_pixel(mlx, x * CUB_SIZE, y * CUB_SIZE, WHITE);
			else if ((*globel)->g_map->map[y][x] == '2')
				ft_draw_pixel(mlx, x * CUB_SIZE, y * CUB_SIZE, ORANGE);
			x++;
		}
		y++;
	}
	draw_circle(globel, mlx, RED);
	calc_line(globel, RED);
}

 void	ft_globle(t_globel **globle)
{
	*globle = malloc(sizeof(t_globel));
	if (!(*globle))
		exit(1);
	(*globle)->g_map = NULL;
	(*globle)->g_map = NULL;
	(*globle)->g_done = NULL;
	(*globle)->mlx = NULL;
}

double	rotation_angle(int c)
{
	double	rot_ang;

	rot_ang = 0.0;
	if (c == 'S')
		rot_ang = (M_PI / 2);
	else if (c == 'W')
		rot_ang = M_PI;
	else if (c == 'E')
		rot_ang = 0.0;
	else if (c == 'N')
		rot_ang = ((M_PI * 3) / 2);
	return (rot_ang);
}

t_player	*ft_player(t_globel *globel)
{
	int	x;
	int	y;

	y = 0;
	while (globel->g_map->map[y])
	{
		x = 0;
		while (globel->g_map->map[y][x])
		{
			if (ft_strchr("SWEN", globel->g_map->map[y][x]))
			{
				globel->g_player->rotation_angle = rotation_angle
					(globel->g_map->map[y][x]);
				globel->g_player->pos_x = (x + 0.5) * CUB_SIZE;
				globel->g_player->pos_y = (y + 0.5) * CUB_SIZE;
				globel->g_player->rotation_speed = 3 * (M_PI / 180);
				globel->g_player->move_speed = MOVE_SPEED;
				break ;
			}
			x++;
		}
		y++;
	}
	return (globel->g_player);
}

t_player	*ft_player_malloc(t_player **player)
{
	*player = malloc(sizeof(t_player));
	if (!(*player))
		exit(1);
	(*player)->derction = -1;
	(*player)->pos_x = -1;
	(*player)->pos_y = -1;
	(*player)->x_move = 0;
	(*player)->y_move = 0;
	return (*player);
}

void	ft_draw(t_globel **globel)
{
	mlx_clear_window((*globel)->mlx->mlx_ptr, (*globel)->mlx->mlx_window);
	draw_window(&(*globel)->mlx, globel);
}

bool	not_wall(t_globel **globel, int lx, int ly)
{
	int	x;
	int	y;

	x = floor(lx / CUB_SIZE);
	y = floor(ly / CUB_SIZE);
	if ((*globel)->g_map->map[y][x] == '1')
		return (true);
	return (false);
}

void	calc_up(t_globel **globel)
{
	int		x;
	int		y;

	x = (*globel)->g_player->pos_x
		+ cos((*globel)->g_player->rotation_angle) * MOVE_SPEED;
	y = (*globel)->g_player->pos_y
		+ sin((*globel)->g_player->rotation_angle) * MOVE_SPEED;
	if (!not_wall(globel, x, y))
	{
		(*globel)->g_player->pos_x = x;
		(*globel)->g_player->pos_y = y;
		ft_draw(globel);
	}
}
void	calc_down(t_globel **globel)
{
	int	x;
	int	y;

	x = (*globel)->g_player->pos_x
		- cos((*globel)->g_player->rotation_angle) * MOVE_SPEED;
	y = (*globel)->g_player->pos_y
		- sin((*globel)->g_player->rotation_angle) * MOVE_SPEED;
	if (!not_wall(globel, x, y))
	{
		(*globel)->g_player->pos_x = x;
		(*globel)->g_player->pos_y = y;
		ft_draw(globel);
	}
}
void	calc_right(t_globel **globel)
{
	(*globel)->g_player->rotation_angle
		+= (*globel)->g_player->rotation_speed;
	ft_draw(globel);
}
void	calc_left(t_globel **globel)
{
	(*globel)->g_player->rotation_angle
		-= (*globel)->g_player->rotation_speed;
	ft_draw(globel);
}

int	keycode(int key, t_globel **globel)
{
	if (key == UP || key == KEY_W)
		calc_up(globel);
	else if (key == DOWN || key == KEY_S)
		calc_down(globel);
	else if (key == RIGHT || key == KEY_D)
		calc_right(globel);
	else if (key == LEFT || key == KEY_A)
		calc_left(globel);
	else if (key == ESC)
		exit(1);
	return (0);
}

int main(int ac, char **av)
{
	t_globel	*globel;
	t_player	*player;
	t_map		*map;
	t_done		done;
	t_mlx		*mlx;

	map = NULL;
	mlx = NULL;
	globel = NULL;
	player = NULL;
	if (ac != 2)
		ft_exit_error("error\n");
	check_file_name(av[1], ".cub");
	ft_globle(&globel);
	globel->g_map = ft_malloc(&map);
	globel->g_done = give_value(&done);
	globel->g_map = parsing_file(av[1], globel);
	(void)player;
	(void)mlx;
	(void)done;
	(void)map;
	(void)globel;
	globel->g_player = ft_player_malloc(&player);
	globel->g_player = ft_player(globel);
	mlx = malloc(sizeof(t_mlx));
	if (!mlx)
		exit(1);
	mlx->mlx_ptr = mlx_init();
	mlx->mlx_window = mlx_new_window(mlx->mlx_ptr,
		(WIFTH * CUB_SIZE), (HEIGHT * CUB_SIZE), "CUB3D");
	globel->mlx = mlx;
	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_window);
	draw_window(&mlx, &globel);
	mlx_hook(mlx->mlx_window, 2, 0, &keycode, &globel);
 	mlx_loop(mlx->mlx_ptr);
	return (0);
}
