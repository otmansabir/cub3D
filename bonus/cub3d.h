/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osabir <osabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:55:22 by osabir            #+#    #+#             */
/*   Updated: 2024/03/26 23:09:41 by osabir           ###   ########.fr       */
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

# define CUB_SIZE 512

# define MINI_CUB 16

# define X_MINI_WID 200
# define Y_MINI_HEI 200
# define X_WIDTH 1280
# define Y_HEIGHT 800

# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123

# define KEY_W 13

# define KEY_A 0
# define KEY_D 2
# define KEY_S 1
# define KEY_K 40
# define KEY_O 31
# define KEY_C 8
# define KEY_V 9

# define ESC 53

# define RADIUS 2
# define ANGLE 60
# define WALL_STRPI_WIDTH 1
# define MINIMAP_FACTOR 0.2
# define MOVE_SPEED 60.0
# define ROTA_ANGLE 1.0
# define LINE_LENGTH 20

# define RED 0xed0505  
# define ORANGE 0xf67c41
# define WHITE 0xfff8f0
# define BLACK 0x000000

typedef struct s_plyr
{
	bool	player_in_map;
	int		i;
	int		j;
}				t_plyr;

typedef struct s_v
{
	double	x;
	double	y;
	double	px;
	double	py;
	int		line;
}			t_v;

typedef struct s_ver
{
	int		dx;
	int		dy;
	int		line;
	double	x;
	double	y;
	double	px;
	double	py;
}			t_var;

typedef struct s_key_event
{
	bool	key_front;
	bool	key_back;
	bool	key_right;
	bool	key_left;
	bool	key_right_ro;
	bool	key_left_ro;
	bool	key_mouse;
	bool	mini_map;
	bool	draws;
}			t_key_event;

typedef struct s_map
{
	char		**map;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			c;
	int			f;
	int			map_x;
	int			map_y;
	bool		read;
}				t_map;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		mini_x;
	double		mini_y;
	double		x_ply;
	double		y_ply;
	int			i;
	int			j;
	double		line_x;
	double		line_y;
	int			derction;
	double		rotation_speed;
	double		rotation_angle;
	double		move_speed;
	double		fov_angle;
	int			num_rays;
}			t_player;

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct s_mouse
{
	int			old_x;
	int			old_y;
}				t_mouse;

typedef struct s_done
{
	bool		no;
	bool		so;
	bool		we;
	bool		ea;
	bool		f;
	bool		c;
}				t_done;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*mlx_window;
	void		*img_ptr;
	char		*buffer;
	int			bpp;
	int			size_line;
	int			endian;
}				t_mlx;

typedef struct s_xpm
{
	void		*img;
	char		*img_addr;
	int			img_width;
	int			img_height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_xpm;

typedef struct s_horizontal
{
	double		x_intercept;
	double		y_intercept;
	double		x_step;
	double		y_step;
	double		found_horiz_x;
	double		found_horiz_y;
	bool		found_horiz_wall_hit;
}				t_horizontal;

typedef struct s_vertical
{
	double		x_intercept;
	double		y_intercept;
	double		x_step;
	double		y_step;
	double		found_vertic_x;
	double		found_vertic_y;
	bool		found_vertic_wall_hit;
}				t_vertical;

typedef struct s_texture
{
	double			ray_distance;
	double			distance_p;
	double			wall_strip_height;
	int				offset_x;
	int				offset_y;
	int				factor;
	unsigned int	*img_data;
}			t_texture;

typedef struct s_cast
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
	struct s_mouse		*mouse;
	struct s_texture	*texture;
}			t_globel;

/*                folder >>  get_line               */

/*    file >> get_next_line_utils.c    */
void			*ft_calloc(size_t count, size_t size);
void			ft_memset(void *b, int c, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strchr(const char *s, int c);

/*     file >> get_next_line.c    */
char			*get_next_line(int fd);

/*                folder >>  mlx_func               */

/*     file >> mlx_func_1.c         */
int				key_release(int key, t_globel **globel);
int				key_press(int key, t_globel **globel);
int				draw_win(t_globel **globel);
void			ft_get_img_xpm(t_globel **globel);
void			make_image(t_globel **globel);

/*     file >> mlx_func_2.c         */
void			ft_esc(t_globel **globel);

/*     file >> mlx_func_3.c         */
void			ft_free_sturct1(t_globel **globel, int i);
void			ft_free_sturct2(t_globel **globel);
void			ft_free_sturct3(t_globel **globel);
void			ft_free_sturct4(t_globel **globel);
int				mouse_move(int x, int y, t_globel **globel);

/*     file >> mlx_func_4.c         */
void			mlx_info(t_globel **globel);
void			ft_globel_free(t_globel **globel, int i);
int				key_exit(t_globel **globel);

/*     file >> move_1.c         */
void			calc_left_ro(t_globel **globel);
void			calc_right_ro(t_globel **globel);
void			calc_down(t_globel **globel);
void			calc_right(t_globel **globel);
void			calc_left(t_globel **globel);

/*     file >> move_2.c         */
bool			not_wall(t_globel **globel, double lx, double ly);
bool			not_walls(t_globel **globel, double lx, double ly);
void			calc_up(t_globel **globel);
void			ft_draw(t_globel **globel);

/*                folder >>  parsing               */

/*     file >> tools_1.c        */
void			check_func(t_globel **globel, char *line, bool x, bool y);
void			check_file_name(char *file_name, char *compre);
void			ft_readcheck(t_globel **globel);
void			ft_just_add(t_globel **globel);
t_map			*parsing_file(char *filename, t_globel *globel);

/*     file >> tools_2.c        */
char			*ft_strnstr(const char *hay, const char *need, size_t len);
char			*check_side(char *line, t_globel **globel);
int				ft_isdigit(int c);
void			ft_test_forma(char *line, t_globel **globel);
int				color_nbr(char *line, t_globel **globel);

/*     file >> tools_3.c        */
void			ft_correctt_digit(char *line, t_globel **globel);
void			checkside22(char *line, int *i, t_globel **globel);
int				checkside2(char *line, t_globel **globel);
char			*get_line(int fd, t_globel **globel);

/*     file >> tools_4.c        */
char			**ft_split(char const *s, char c);

/*     file >> tools_5.c        */
int				ft_atoi(const char *str);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_charjoin(char *s1, char c);
char			*ft_strdup(const char *s1);

/*     file >> tools_6.c        */
int				ft_strlen(const char *str);
t_map			*ft_malloc(t_globel **globel);
t_done			*give_value(t_globel **globel);
int				ft_check_map(char *line);

/*     file >> tools_7.c        */
void			add_this_function(t_globel **globel, char **map);
void			char_map(char *line, t_globel **globel);
bool			right_side(char *line, int i);
bool			left_side(char *line, int i);
char			**one_arry(char *line);

/*     file >> tools_8.c        */
char			**to_arry(char *line, char **map);
char			**parsing_map(char *line, char **map, t_globel **globel);
int				len_map_x(char **map, t_globel **globel);
int				len_map_y(char **map, t_globel **globel);
void			ft__last_check_map(char **map, t_plyr *plyr, t_globel **globel);

/*     file >> tools_9.c        */
bool			ft_left(char **line, int i, int j);
bool			ft_right(char **line, int i, int j);
bool			ft_down(char **line, int i, int j);
bool			ft_up(char **line, int i, int j);
void			ft_last_check_map(char **map, t_globel **globel);

/*     file >> tools_10.c        */
char			*new_line(char *line, int size_map, t_globel **globel);
char			**make_map_same_size(char **map, int len,
					int size_map, t_globel **globel);
void			ft_no(t_globel **globel, char *line);
void			parsing_file_p2(t_globel **globel, char *line);
void			ft_map(t_globel **globel, char *line);

/*     file >> tools_11.c        */
void			ft_so(t_globel **globel, char *line);
void			ft_we(t_globel **globel, char *line);
void			ft_ea(t_globel **globel, char *line);
void			ft_c(t_globel **globel, char *line);
void			ft_f(t_globel **globel, char *line);

/*     file >> tools_12.c        */
void			my_put_pixel(t_globel **globel, int x, int y, int color);
void			ft_exit_error(char *error, t_globel **globel);
void			ft_putstr_fd(char *s, int fd, t_globel **globel);
bool			not_wall1(t_globel **globel, int lx, int ly);
void			ft_putchar_fd(char c, int fd);

/*                folder >>  raycasting               */

/*     file >> minimap.c        */
void			draw_line(t_globel **globel, int color);
void			calc_minimap(t_globel **globel);
void			calc_minimap(t_globel **globel);
void			calc_line(t_globel **globel, int color);
void			draw_minimap(t_globel **globel);

/*     file >> ray_1.c        */
void			where_i_looking_to(t_globel **globel, double rayangle);
double			normlize_angle(double rayangle);
void			ray_casting(t_globel **globel, double rayangle, int column);
void			draw_ray(t_globel **globel);
void			draw_window(t_globel **globel);

/*     file >> ray_2.c        */
void			set_val(t_globel **globel, double x, double y);
void			clac_horiz(t_globel **globel, double rayangle);
void			horiz(t_globel **globel, double rayangle);

/*     file >> ray_3.c        */
void			set_val_v(t_globel **globel, double x, double y);
void			calc_vert(t_globel **globel, double rayangle);
void			vertic(t_globel **globel, double rayangle);

double			distance(double x1, double y1, double x2, double y2);
void			ft_clalc_ver_hor(t_globel **globel, double *h, double *v);
void			calc_horiz_vertic(t_globel **globel);

/*     file >> ray_5.c        */
void			put_image(t_globel **globel);
t_xpm			*image(t_globel **globel, double rayangle);
void			calc_image(t_globel **globel, t_xpm **images);
void			calc_top_botton(t_globel **globel, double rayangle \
					, int *top, int *bottom);
void			render_3d_projecte_walls(t_globel **globel, int column \
						, double rayangle);

/*     file >> ray_6.c        */
void			ft_draw_pixel(t_globel **globel, int x, int y, int color);

/*                folder >>  struct              */

/*     file >> player.c        */
double			rotation_angle(int c);
void			set_plyr(t_globel **globel, int x, int y);
void			ft_player(t_globel **globel);
t_player		*ft_player_malloc(t_globel **globel);

/*     file >> struct_1.c        */
t_mouse			*mouse_var(t_globel **globel);
t_xpm			*aloc_xpm(t_globel **globel);
t_cast			*aloc_cast(t_globel **globel);
t_texture		*aloc_texture(t_globel **globel);
t_globel		*everthing(t_globel *globel);

/*     file >> struct_2.c        */
t_key_event		*make_null(t_globel **globel);
t_horizontal	*aloc_horzi(t_globel **globel);
t_vertical		*aloc_vert(t_globel **globel);
t_mlx			*mlx_aloc(t_globel **globel);

#endif