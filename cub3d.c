/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:23:35 by osabir            #+#    #+#             */
/*   Updated: 2024/02/09 18:58:00 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void draw_ray_line(t_globel **globle, int ray_x, int ray_y)
{
	int		dx;
	int		dy;
	int		line;
	double	x;
	double	y;
	double	px;
	double	py;

	dx = ray_x - (*globle)->g_player->pos_x;
	dy = ray_y - (*globle)->g_player->pos_y;
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
		mlx_pixel_put((*globle)->mlx->mlx_ptr, (*globle)->mlx->mlx_window, (int)px, (int)py, RED);
		px += x;
		py += y;
	}
}

void	calc_rays(t_globel **globle, double rayangle)
{
	double	x;
	double	y;

	x = (*globle)->g_player->pos_x;
	y = (*globle)->g_player->pos_y;
	x += cos(rayangle) * LINE_LENGTH;
	y += sin(rayangle) * LINE_LENGTH;
	draw_ray_line(globle, x, y);
}

double	normlize_angle(double rayangle)
{
	rayangle = fmod(rayangle, (2 * M_PI));
	if (rayangle < 0)
		rayangle += 2 * M_PI;
	return (rayangle);
}

void	horiz(t_globel **globel, double rayangle)
{
	long	next_horiz_x;
	long	next_horiz_y;

	(*globel)->cast->horizontal->found_horiz_wall_hit = false;
	// calc y_intercept
	(*globel)->cast->horizontal->y_intercept
		= floor((*globel)->g_player->pos_y / CUB_SIZE) * CUB_SIZE;
	if ((*globel)->cast->ray_facing_down)
		(*globel)->cast->horizontal->y_intercept += CUB_SIZE;
	// calc x_intercept
	(*globel)->cast->horizontal->x_intercept = (*globel)->g_player->pos_x
		+ ((*globel)->cast->horizontal->y_intercept
			- (*globel)->g_player->pos_y) / tan(rayangle);
	// calc y_step
	(*globel)->cast->horizontal->y_step = CUB_SIZE;
	if ((*globel)->cast->ray_facing_up)
		(*globel)->cast->horizontal->y_step *= -1;
	// calc x_step
	(*globel)->cast->horizontal->x_step = CUB_SIZE / tan(rayangle);
	if ((*globel)->cast->ray_facing_left
		&& (*globel)->cast->horizontal->x_step > 0)
		(*globel)->cast->horizontal->x_step *= -1;
	if ((*globel)->cast->ray_facing_right
		&& (*globel)->cast->horizontal->x_step < 0)
		(*globel)->cast->horizontal->x_step *= -1;

	next_horiz_x = (*globel)->cast->horizontal->x_intercept;
	next_horiz_y = (*globel)->cast->horizontal->y_intercept;

	if ((*globel)->cast->ray_facing_up)
		next_horiz_y--;
	printf("x_intercept = %ld\n", (*globel)->cast->horizontal->x_intercept);
	printf("y_intercept = %ld\n", (*globel)->cast->horizontal->y_intercept);
	printf("x_step = %ld\n", (*globel)->cast->horizontal->x_step);
	printf("y_step = %ld\n", (*globel)->cast->horizontal->y_step);
	printf("play_x = %d\n", (*globel)->g_player->pos_x);
	printf("play_y = %d\n", (*globel)->g_player->pos_y);
	printf("angle = %f\n\n\n", rayangle);

	long	tmp_horiz_x = next_horiz_x;
	long	tmp_horiz_y = next_horiz_y;
	while (next_horiz_x >= 0 && next_horiz_x
		<= (*globel)->g_map->map_x * CUB_SIZE
		&& next_horiz_y >= 0 && next_horiz_y
		<= (*globel)->g_map->map_y * CUB_SIZE)
	{
		if (not_wall(globel, next_horiz_x, next_horiz_y))
		{
			(*globel)->cast->horizontal->found_horiz_wall_hit = true;
			(*globel)->cast->horizontal->found_horiz_x = next_horiz_x;
			(*globel)->cast->horizontal->found_horiz_y = next_horiz_y;
			// draw_ray_line(globel, next_horiz_x, next_horiz_y);
			return ;
		}
		else
		{
			tmp_horiz_x = next_horiz_x;
			tmp_horiz_y = next_horiz_y;
			next_horiz_x += (*globel)->cast->horizontal->x_step;
			next_horiz_y += (*globel)->cast->horizontal->y_step;
			// printf("next_horiz_x = %ld\n", next_horiz_x);
			// printf("next_horiz_y = %ld\n\n\n", next_horiz_y);
		}
	}
	// (*globel)->cast->horizontal->found_horiz_wall_hit = true;
	// (*globel)->cast->horizontal->found_horiz_x = tmp_horiz_x;
	// (*globel)->cast->horizontal->found_horiz_y = tmp_horiz_y;
	// printf("OK\n");
	// draw_ray_line(globel, tmp_horiz_x, tmp_horiz_y);
}

void	where_i_looking_to(t_globel **globel, double rayangle)
{
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

void	vertic(t_globel **globel, double rayangle)
{
	long	next_vertic_x;
	long	next_vertic_y;

	(*globel)->cast->vertical->found_vertic_wall_hit = false;
	// calc x_intercept
	(*globel)->cast->vertical->x_intercept
		= floor((*globel)->g_player->pos_x / CUB_SIZE) * CUB_SIZE;
	if ((*globel)->cast->ray_facing_right)
		(*globel)->cast->vertical->x_intercept += CUB_SIZE;
	// calc y_intercept
	(*globel)->cast->vertical->y_intercept = (*globel)->g_player->pos_y
		+ ((*globel)->cast->vertical->x_intercept
			- (*globel)->g_player->pos_x) * tan(rayangle);
	// calc x_step
	(*globel)->cast->vertical->x_step = CUB_SIZE;
	if ((*globel)->cast->ray_facing_left)
		(*globel)->cast->vertical->x_step *= -1;
	// calc y_step
	(*globel)->cast->vertical->y_step = CUB_SIZE * tan(rayangle);
	if ((*globel)->cast->ray_facing_up
		&& (*globel)->cast->vertical->y_step > 0)
		(*globel)->cast->vertical->y_step *= -1;
	if ((*globel)->cast->ray_facing_down
		&& (*globel)->cast->vertical->y_step < 0)
		(*globel)->cast->vertical->y_step *= -1;

	next_vertic_x = (*globel)->cast->vertical->x_intercept;
	next_vertic_y = (*globel)->cast->vertical->y_intercept;

	if ((*globel)->cast->ray_facing_left)
		next_vertic_x--;

	printf("x_intercept = %ld\n", (*globel)->cast->vertical->x_intercept);
	printf("y_intercept = %ld\n", (*globel)->cast->vertical->y_intercept);
	printf("x_step = %ld\n", (*globel)->cast->vertical->x_step);
	printf("y_step = %ld\n", (*globel)->cast->vertical->y_step);
	printf("play_x = %d\n", (*globel)->g_player->pos_x);
	printf("play_y = %d\n", (*globel)->g_player->pos_y);
	printf("angle = %f\n\n\n", rayangle);

	while (next_vertic_x >= 0 && next_vertic_x
		<= (*globel)->g_map->map_x * CUB_SIZE
		&& next_vertic_y >= 0 && next_vertic_y
		<= (*globel)->g_map->map_y * CUB_SIZE)
	{
		if (not_wall(globel, next_vertic_x, next_vertic_y))
		{
			(*globel)->cast->vertical->found_vertic_wall_hit = true;
			(*globel)->cast->vertical->found_vertic_x = next_vertic_x;
			(*globel)->cast->vertical->found_vertic_y = next_vertic_y;
			// draw_ray_line(globel, next_vertic_x, next_vertic_y);
			break ;
		}
		else
		{
			next_vertic_x += (*globel)->cast->vertical->x_step;
			next_vertic_y += (*globel)->cast->vertical->y_step;
			// printf("next_horiz_x = %ld\n", next_horiz_x);
			// printf("next_horiz_y = %ld\n\n\n", next_horiz_y);
		}
	}
}

double	distance(int x1, int y1, long x2, long y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	calc_horiz_vertic(t_globel **globel)
{
	double	horiz_distance;
	double	vertic_distance;

	horiz_distance = 0;
	vertic_distance = 0;
	(*globel)->cast->its_hit_vertical = false;
	if ((*globel)->cast->horizontal->found_horiz_wall_hit)
		horiz_distance = distance((*globel)->g_player->pos_x,
		(*globel)->g_player->pos_y, (*globel)->cast->horizontal->found_horiz_x, (*globel)->cast->horizontal->found_horiz_y);
	if (!(*globel)->cast->horizontal->found_horiz_wall_hit)
		horiz_distance = LONG_MAX;
	if ((*globel)->cast->vertical->found_vertic_wall_hit)
		vertic_distance = distance((*globel)->g_player->pos_x, (*globel)->g_player->pos_y, (*globel)->cast->vertical->found_vertic_x, (*globel)->cast->vertical->found_vertic_y);
	if (!(*globel)->cast->vertical->found_vertic_wall_hit)
		vertic_distance = LONG_MAX;
	if (horiz_distance < vertic_distance)
	{
		(*globel)->cast->wall_hit_x = (*globel)->cast->horizontal->found_horiz_x;
		(*globel)->cast->wall_hit_y = (*globel)->cast->horizontal->found_horiz_y;
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

void	ray_casting(t_globel **globel, double rayangle, int column)
{
	(void)column;
	rayangle = normlize_angle(rayangle);
	where_i_looking_to(globel, rayangle);
	horiz(globel, rayangle);
	vertic(globel, rayangle);
	calc_horiz_vertic(globel);
	draw_ray_line(globel, (*globel)->cast->wall_hit_x, (*globel)->cast->wall_hit_y);
}

void	draw_ray(t_globel **globel)
{
	int		column;
	int		i;
	double	rayangle;

	column = 0;
	i = 0;
	rayangle = (*globel)->g_player->rotation_angle - ((*globel)->g_player->fov_angle / 2);
	// while (i < 1)
	while (i < (*globel)->g_player->num_rays)
	{
		// calc_rays(globel, rayangle);
		ray_casting(globel, rayangle, column);
		rayangle += (*globel)->g_player->fov_angle / (*globel)->g_player->num_rays;
		column++;
		i++;
	}
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
	draw_ray(globel);
	draw_circle(globel, mlx, RED);
	// calc_line(globel, RED);
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
				globel->g_player->rotation_speed = 2 * (M_PI / 180);
				globel->g_player->move_speed = MOVE_SPEED;
				globel->g_player->fov_angle = ANGLE * (M_PI / 180);
				globel->g_player->num_rays
					= (globel->g_map->map_x * CUB_SIZE) / WALL_STRPI_WIDTH;
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

t_cast	*malloc_cast(void)
{
	t_cast			*cast;
	t_horizontal	*horiz;
	t_vertical		*vert;

	cast = malloc(sizeof(t_cast));
	if (!cast)
		exit(1);
	cast->ray_facing_down = false;
	cast->ray_facing_up = false;
	cast->ray_facing_right = false;
	cast->ray_facing_left = false;
	horiz = malloc(sizeof(t_horizontal));
	if (!horiz)
		exit(1);
	vert = malloc(sizeof(t_vertical));
	if (!vert)
		exit(1);
	cast->horizontal = horiz;
	cast->vertical = vert;
	return (cast);
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
	globel->cast = malloc_cast();
	mlx->mlx_ptr = mlx_init();
	mlx->mlx_window = mlx_new_window(mlx->mlx_ptr,
		(globel->g_map->map_x * CUB_SIZE),
		(globel->g_map->map_y * CUB_SIZE), "CUB3D");
	globel->mlx = mlx;
	mlx_clear_window(mlx->mlx_ptr, mlx->mlx_window);
	draw_window(&mlx, &globel);
	mlx_hook(mlx->mlx_window, 2, 0, &keycode, &globel);
 	mlx_loop(mlx->mlx_ptr);
	return (0);
}
