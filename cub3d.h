#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <limits.h>
# include <stdbool.h>
# include <math.h>
# if defined(__APPLE__)
#  include <key_macos.h>
# else
#  include </home/otmansabir/minilibx_linux/mlx.h>
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# ifndef M_PI
#  define M_PI (3.14159265358979323846264338327950288)
# endif


# define CUB_SIZE 32

# define UP 65362
# define DOWN 65364
# define RIGHT 65363
# define LEFT 65361

# define KEY_W 119
# define KEY_A 97
# define KEY_D 100
# define KEY_S 115

# define ESC 65307

# define RADIUS 5
# define LINE_LENGTH 20

// # define ROTATIONSPEED (M_PI / 2)



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
	int	pos_x;
	int	pos_y;
	int	derction;
	double rotation_speed;
	double move_speed;
	double rotation_angle;
	int	x_move;
	int	y_move;
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
}			t_mlx;

typedef	struct s_globel
{
	struct s_map		*g_map;
	struct s_mlx		*mlx;
	struct s_player		*g_player;
	struct s_done		*g_done;
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
void    ft_exit_error(char *error);

//  file get_next_line_utils.c
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);\
void	ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);

//	file >> tools_1.c
char	*check_side(char *line);
t_map	*ft_malloc(t_map **map);
void	ft_free_t_map_and_error(t_map **map);
int 	ft_strlen(const char *str);
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
void draw_circle(t_globel **globel, t_mlx **mlx, int color);

#endif