#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "get_next_line.h"

# define GRID_LEN 40
# define FALSE 0
# define TRUE 1

typedef struct s_data
{
	char	*av;
	int		fd;
	char	*line;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	char	*ceiling;
	int		intfloor;
	int		intceiling;
	int		R;
	int		G;
	int		B;
	int		x;
	int		y;
	int		d[4];
}	t_data;


typedef struct  s_ray
{
	double	pos_x;
	double	pos_y;
	double	radius;
	double	dir_x;
	double	dir_y;
	double	cam_plane_len;
}	t_ray;

typedef struct	s_3d
{
	double	diagonal;
	double	ray_x;
	double	ray_y;
	double	d;
	double	ratio;
	double	height;
	double	bottom;
}	t_3d;

typedef struct s_img
{
	void	*img[4];
	char	*addr[4];
	int		bpp;
	int		size;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	t_data	data;
	t_ray	ray;
	t_3d	ddd;	
	t_img	img;
	void	*mlx;
	void	*win;
	void	*mini;
	char	**map;
	char	**tmp;
	int		mapWidth;
	int		mapHeight;
	int		screenWidth;
	int		screenHeight;
}	t_mlx;

/*		utils.c		*/
int		ft_is_space(char c);
size_t	ft_strlen(char *str);
char	*ft_strcpy(t_mlx *mlx, char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_is_num(char c);

/*		utils2.c		*/
int		ft_linelen(char *line);
char	*ft_linecpy(t_mlx *mlx, char *line);
int		ft_arrlen(char **arr);
void	ft_bzero(void *str, size_t size);
void	*ft_calloc(t_mlx *mlx, size_t len, size_t size);

/*		utils3.c		*/
void	ft_pixel_put(t_mlx *mlx, double x, double y, int tex_y);
int		ft_get_dir(t_mlx *mlx);

/*		ft_get_info.c		*/
void	ft_get_texture(t_mlx *mlx, char *line);
void	ft_syntax_of_color(t_mlx *mlx, char *str);
int		ft_edit_color(t_mlx *mlx, char *str);
void	ft_get_info(t_mlx *mlx);

/*		ft_get_map.c		*/
void	ft_syntax_of_map(t_mlx *mlx, char *line);
void 	ft_add_line_to_arr(t_mlx *mlx);
int 	ft_is_empty_line(char *line);
void	ft_get_map(t_mlx *mlx);

/*		ft_is_valid_map.c		*/
void    ft_get_dir_vector(t_mlx *mlx, char c);
void    ft_find_player(t_mlx *mlx, int player, int x, int y);
void    ft_dfs(t_mlx *mlx, int x, int y, int k);
void	ft_is_valid_map(t_mlx *mlx);

/*		ft_make_map_to_square		*/
int 	ft_find_longest_len(char **map);
void    ft_put_space_in_first_and_last_array(t_mlx *mlx);
void    ft_put_space_in_first_and_last_slot_of_array(t_mlx *mlx);
void    ft_copy_map(t_mlx *mlx);
void    ft_make_map_to_square(t_mlx *mlx);

/*		ft_draw.c		*/
void	ft_draw_rectagle(t_mlx *mlx, int x, int y, int color);
void	ft_draw_grid(t_mlx *mlx, char val, int color);
void	ft_draw_player(t_mlx *mlx, int color);

/*		ft_key_press.c		*/
int		ft_end_game(t_mlx *mlx);
int		ft_is_wall(t_mlx *mlx, double px, double py);
void	ft_remove_screen(t_mlx *mlx);
void	ft_move(t_mlx *mlx, double theta);
int		ft_key_press(int keycode, t_mlx *mlx);

/*		ft_draw_ray.c		*/
void    ft_draw_cam_ray(t_mlx *mlx, double dir_x, double dir_y, int color);
void    ft_draw_cam_plane(t_mlx *mlx);
void    ft_rotate(t_mlx *mlx, double angle);

/*		ft_draw_line.c		*/
void 	ft_draw_line_1(t_mlx *mlx, double y[2], double m);
void 	ft_draw_line_2(t_mlx *mlx, double y[2], double m);
void 	ft_draw_line_3(t_mlx *mlx, double x[2], double y[2], double m);
void	ft_draw_line_4(t_mlx *mlx, double x[2], double y[2], double m);
void    ft_draw_line(t_mlx *mlx, double x[2], double y[2]);

/*		ft_distance.c		*/
void    ft_distance(t_mlx *mlx);
void    ft_draw_wall(t_mlx *mlx, double x);
void    ft_draw_ceiling(t_mlx *mlx, double x, int color);
void    ft_draw_floor(t_mlx *mlx, double x, int color);

/*		ft_img.c		*/
void	ft_mlx_img(t_mlx *mlx);

/*		ft_error.c		*/
void	ft_free_map(t_mlx *mlx);
void	ft_free_tmp(t_mlx *mlx);
void	ft_free_line(t_mlx *mlx);
void	ft_free_mlx(t_mlx *mlx);

#endif
