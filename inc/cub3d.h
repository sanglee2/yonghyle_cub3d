/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:06:43 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/26 20:17:29 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*	key binding	*/
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_L 123
# define KEY_R 124
# define KEY_ESC 53

/* key 이동비율 */
# define LIMITS	2.0
# define M 0.1
# define ROT_RATIO 10

/* texture에 필요한 거기 */
# define TEXWIDTH		64
# define TEXHEIGHT		64

/* texture에 필요한 방향 */
# define NO			0
# define SO			1
# define WE			2
# define EA			3
# define FL			4
# define CE			5

typedef struct s_color
{
	int	comma;
	int	element;
	int	num_flag;
	int	serial_comma;
}	t_color;

typedef struct s_data
{
	char		*av;
	int			fd;
	char		*line;			
	char		**information;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*floor;
	char		*ceiling;
	int			intfloor;		
	int			intceiling;		
	int			red;
	int			green;
	int			blue;		
	int			x;				
	int			y;				
}	t_data;

typedef struct s_ray
{
	double	dir_x;				
	double	dir_y;
	double	pos_x;				
	double	pos_y;
	double	plane_x;			
	double	plane_y;
	double	rdir_x;				
	double	rdir_y;
	int		map_x;
	int		map_y;
	double	vardist_x;
	double	vardist_y;
	int		step_x;
	int		step_y;
	double	initdist_x;
	double	initdist_y;
	int		orthogonal;
	double	plane_hitdist;
	int		tex_x;
	int		tex_y;
	int		wallheight;
	int		wallstart;
	int		wallend;
	double	ratio;
	double	texpos;
}	t_ray;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
	int		width;
	int		height;
}	t_img_data;

typedef struct s_mlx
{
	void		*mlx;
	t_img_data	img_data[4];
	t_img_data	img;
	t_data		data;
	t_color		color;
	t_ray		ray;
	void		*win;
	void		*image;
	char		**map;
	char		**tmp;
	int			map_width;
	int			map_height;
	int			screen_width;
	int			screen_height;
	int			keycode;
}	t_mlx;

/*		ft_draw_texture.c		*/
void	ft_draw_ceiling(t_mlx *mlx, int x, int wallstart, int color);
void	ft_draw_floor(t_mlx *mlx, int x, int wallend, int color);

/*		ft_error.c		*/
void	ft_free_map(t_mlx *mlx);
void	ft_free_tmp(t_mlx *mlx);
void	ft_free_info(t_data *data);
void	ft_free_line(t_mlx *mlx);
void	ft_free_mlx(t_mlx *mlx);

/*		ft_get_info.c		*/
int		ft_check_identifier(char *str);
void	ft_check_texture_element(t_mlx *mlx, t_data *data);
int		ft_open_file(t_mlx *mlx, char *path);
void	ft_check_valid_path(t_mlx *mlx, int identifier, char *path);
int		set_texture_element(t_mlx *mlx, t_data *data);

/*		ft_get_info2.c		*/
void	ft_get_texture(t_mlx *mlx);
void	ft_syntax_of_color(t_mlx *mlx, char *str);
void	ft_str_to_int(t_mlx *mlx, char *str);
int		ft_edit_color(t_mlx *mlx, char *str);
void	ft_get_info(t_mlx *mlx);

/*		ft_get_map.c		*/
void	ft_syntax_of_map(t_mlx *mlx, char *line);
void	ft_line_to_map(t_mlx *mlx);
int		ft_is_empty_line(char *line);
void	ft_get_map(t_mlx *mlx);

/*		ft_img.c		*/
void	ft_init_texture(t_mlx *mlx);
void	ft_load_texture(t_mlx *mlx);

/*		ft_is_valid_map.c		*/
void	ft_get_dir_vector(t_mlx *mlx, char c);
void	ft_find_player(t_mlx *mlx, int player, int x, int y);
void	ft_is_valid_map(t_mlx *mlx);

/*		ft_key_press.c		*/
int		ft_end_game(t_mlx *mlx);
void	ft_go_forward(t_mlx *mlx, t_ray *ray);
void	ft_go_backward(t_mlx *mlx, t_ray *ray);
void	ft_go_left(t_mlx *mlx, t_ray *ray);
void	ft_go_right(t_mlx *mlx, t_ray *ray);

/*		ft_key_press2.c		*/
void	ft_move(int keycode, t_mlx *mlx);
int		ft_key_press(int keycode, t_mlx *mlx);

/*		ft_mlx_set.c		*/
void	window_init(t_mlx *mlx);
void	image_init(t_mlx *mlx);

/*		ft_raycast_algo.c		*/
void	ft_set_coordinate(t_ray *ray);
void	ft_set_dda(t_ray *ray);
void	ft_perform_dda(t_mlx *mlx, t_ray *ray);
void	ft_calcul_distance(t_ray *ray);
void	ft_draw_vertical_line(t_mlx *mlx, int x);

/*		ft_rotate.c				*/
void	ft_key_r(t_ray *ray);
void	ft_key_l(t_ray *ray);

/*		ft_set_map		*/
int		ft_find_longest_len(char **map);
int		ft_max_width(char **map);
void	*ft_memset(void *ptr, int value, size_t num);
void	ft_set_map(t_mlx *mlx);

/*		ft_split.c				*/
int		is_space(char c);
char	*ft_strncpy(char *s1, char *s2, int n);
char	**ft_split(char *str, int i, int j, int k);

/* 		ft_test_valid_map1.c		*/
void	check_map_is_closed(char **tmp, t_mlx *mlx);
void	check_is_surrouned(char **tmp, int y, int x, t_mlx *mlx);

/* 		ft_test_valid_map2.c		*/
int		is_empty_space(char c);
void	check_north_is_empty(t_mlx *mlx, char **tmp, int y, int x);
void	check_south_is_empty(t_mlx *mlx, char **tmp, int y, int x);
void	check_east_is_empty(t_mlx *mlx, char **tmp, int y, int x);
void	check_west_is_empty(t_mlx *mlx, char **tmp, int y, int x);

/*		ft_texture.c			*/
void	ft_get_wall_x(t_ray *ray, t_mlx *mlx);
void	user_mlx_pixel_put(t_img_data *img, int x, int y, int color);
void	ft_get_walltexture(t_ray *ray, t_mlx *mlx, int x);

/*		utils.c		*/
int		ft_is_space(char c);
size_t	ft_strlen(char *str);
char	*ft_strdup(t_mlx *mlx, char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_is_num(char c);

/*		utils2.c		*/
int		ft_linelen(char *line);
char	*ft_linecpy(t_mlx *mlx, char *line);
int		ft_arrlen(char **arr);
void	ft_bzero(void *str, size_t size);
void	*ft_calloc(t_mlx *mlx, size_t len, size_t size);

/*		utils3.c		*/
char	*ft_strcpy(char *str1, char *str2);

/*		ft_test.c		*/
void	check_map_is_closed(char **tmp, t_mlx *mlx);
int		is_empty_space(char c);
void	check_is_surrouned(char **tmp, int y, int x, t_mlx *mlx);

#endif
