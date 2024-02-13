/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:55:22 by osabir            #+#    #+#             */
/*   Updated: 2024/02/13 18:57:40 by osabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <limits.h>
# include <stdbool.h>
# include <math.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# define CUB_SIZE 32

# define WIDTH 640
# define HEIGHT 400

# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123

# define KEY_W 13
# define KEY_A 0
# define KEY_D 2
# define KEY_S 1

# define ESC 53

# define RADIUS 3
# define ANGLE 60
# define WALL_STRPI_WIDTH 1
# define MINIMAP_FACTOR 0.2
# define MOVE_SPEED 12.0
# define ROTA_ANGLE 8
# define LINE_LENGTH 30

# define RED 0xed0505  
# define ORANGE 0xf67c41
# define WHITE 0xfff8f0
# define BLACK 0x000000

typedef struct s_key_event
{
	bool	key_front;
	bool	key_back;
	bool	key_right;
	bool	key_left;
	bool	key_esc;
}			t_key_event;

typedef struct s_map
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		c;
	int		f;
	int		map_x;
	int		map_y;
}			t_map;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		line_x;
	double		line_y;
	int		derction;
	double	rotation_speed;
	double	rotation_angle;
	double	move_speed;
	double	fov_angle;
	int		num_rays;
}			t_player;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}			t_color;

typedef struct s_done
{
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
	bool	f;
	bool	c;
}			t_done;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*mlx_window;
	void	*img_ptr;
	char	*buffer;
	int		bpp;
	int		size_line;      
	int		endian;      
}			t_mlx;

typedef struct s_xpm
{
	void	*img;
	int		img_width;
	int		img_height;
}			t_xpm;

typedef	struct s_horizontal
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	double	found_horiz_x;
	double	found_horiz_y;
	bool	found_horiz_wall_hit;
}			t_horizontal;

typedef	struct s_vertical
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	double	found_vertic_x;
	double	found_vertic_y;
	bool	found_vertic_wall_hit;
}			t_vertical;

typedef	struct s_cast
{
	struct s_horizontal		*horizontal;
	struct s_vertical		*vertical;
	double					wall_hit_x;
	double					wall_hit_y;
	double					distance;
	bool					ray_facing_down;
	bool					ray_facing_up;
	bool					ray_facing_right;
	bool					ray_facing_left;
	bool					its_hit_vertical;
}			t_cast;


typedef struct s_globel
{
	struct s_map		*g_map;
	struct s_mlx		*mlx;
	struct s_player		*g_player;
	struct s_done		*g_done;
	struct s_cast		*cast;
	struct s_key_event	*event;
	struct s_xpm		*so;
	struct s_xpm		*no;
	struct s_xpm		*we;
	struct s_xpm		*ea;
}			t_globel;

char	*ft_strnstr(const char *hay, const char *need, size_t len);
int		color_nbr(char *line);
int		ft_isdigit(int c);

int		checkside2(char *line);
void	ft_test_forma(char *line);
char	*ft_strnstr(const char *hay, const char *need, size_t len);

//	file >> cub3d.c
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_exit_error(char *error);

//  file get_next_line_utils.c
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);

//	file >> tools_1.c
char	*check_side(char *line);
t_map	*ft_malloc(t_map **map);
void	ft_free_t_map_and_error(t_map **map);
int		ft_strlen(const char *str);
t_done	*give_value(t_done *done);
int		ft_check_map(char *line);
t_map	*parsing_file(char *filename, t_globel *globle);
char	**parsing_map(char *line, char **map);


//	file >> tools_3.c
char	*get_line(int fd);

//   file >> tools_4.c
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_charjoin(char *s1, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(const char *s1);

//   NULL
void	draw_circle(t_globel **globel, t_mlx **mlx, int color);

#endif