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
# define MOVE_RATIO 0.1
# define ROT_RATIO 10


/* texture에 필요한 거기 */
# define TEXWIDTH		64	
# define TEXHEIGHT		64	

/* texture에 필요한 방향 */
# define NO			0
# define SO			1
# define WE			2
# define EA			3




typedef struct s_data
{
	char		*av;			// 터미널에서 받은 argv 저장.
	int			fd;				// 맵파일 fd값 저장.
	char		*line;			// 맵정보의 1줄.
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*floor;
	char		*ceiling;
	int			intfloor;		// RGB값 쭉 나열해 놓은 것.
	int			intceiling;		// RGB값 쭉 나열해 놓은 것.
	int			R;
	int			G;
	int			B;
	int			d[4];			// dfs용 배열
	int			x;				// 플레이어의 위치 좌표.
	int			y;				// 플레이어의 위치 좌표.
}	t_data;


typedef struct  s_ray			// 광선과 관련한 필요한 모든 것.
{
	double	dir_x;				// 플레이어의 방향벡터 -> pdir 바꿀 것.
	double	dir_y;
	double	pos_x;				// data.x * GRID_LEN map -> 계속 double로 유지하는 게 맞을까?
	double	pos_y;
	double	plane_x;			// 멤버변수 어디까지 - 고민시점. // -> 카메라 평면의 방향벡터
	double 	plane_y;
	double	rdir_x;				// 광선의 방향벡터 -> DDA 알고리즘 핵심.
	double	rdir_y;
	int		mapX;
	int		mapY;				// int 좌표계로 map 처음 세팅할 때.
	double	varDistX;			// 좌표 간격마다 변하는 길이.
	double	varDistY;
	int		stepX;				// 좌표 1칸의 크기 & 방향.
	int		stepY;
	double	initDistX;			// 실제 좌표서 초기값 길이.
	double	initDistY;
	int		orthogonal;			// 직선과 만나는 벽면 -> 나중에 #define해서 대입하기.
	double	plane_hitDist;
	int		tex_x;
	int		tex_y;
	double	radius;
	double	cam_plane_len;
	int		wallheight;			// 지우거나, 대처할 거라고 생각해야 하는 것들
	int		wallstart;
	int		wallend;
	double	ratio;
	double	texpos;
}	t_ray;

typedef struct	s_3d			// 3d 관련된 부분 구조체.
{
	double	diagonal;
	double	ray_x;
	double	ray_y;
	double	d;					// 벽까지의 거리.
	double	ratio;
	double	height;				// 그려야 할 벽의 높이.	
	double	bottom;
}	t_3d;

// typedef struct s_img
// {
// 	void	*img[4];
// 	char	*addr[4];
// 	int		width;
// 	int		height;
// 	int		bpp;
// 	int		size;
// 	int		endian;
// 	char	*pixel;		// 이 네놈 왜 필요한지 모르겠다.	
// 	char	**buffer;	
// }	t_img;


typedef struct s_img_data	// img 와 addr 뿐 아니라 전체를 구조체 배열을 갖고 있어야 한다.
{
	void	*img;
	char	*addr;
	int		bpp;
	int		length;
	int		endian;
	int		width;			// texwidth -> #define 안 해도 됨.
	int		height;
} t_img_data;


typedef struct s_mlx
{
	void	*mlx;
	t_img_data	img_data[4];	// 포인터 로써도 다재다능하게 쓰일 수 있나.	
	t_img_data	img;
	t_data	data;
	t_ray	ray;
	t_3d	ddd;				// 3d 이놈 뭔데?!	
	// int		texture[TEXHEIGHT][TEXWIDTH];
	int		linenum;
	void	*win;
	void	*image;
	char	**map;
	char	**tmp;
	int		mapWidth;			// map 배열 너비.
	int		mapHeight;			// map 배열 높이.
	int		screenWidth;
	int		screenHeight;
	int		keycode;
}	t_mlx;

/*		utils.c		*/
int		ft_is_space(char c);
size_t	ft_strlen(char *str);
char	*ft_str_to_mlx(t_mlx *mlx, char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_is_num(char c);
char	*ft_strcpy(char *str1, char *str2);

/*		utils2.c		*/
int		ft_linelen(char *line);
char	*ft_linecpy(t_mlx *mlx, char *line);
int		ft_arrlen(char **arr);
void	ft_bzero(void *str, size_t size);
void	*ft_calloc(t_mlx *mlx, size_t len, size_t size);

/*		ft_pixel_utils.c		*/
// void	ft_pixel_put(t_mlx *mlx, double x, double y, int tex_y);
void ft_pixel_put(t_mlx *mlx, int x, int y, int tex_y);
int		ft_get_dir(t_mlx *mlx);

/*		ft_get_info.c		*/
void	ft_file_check(t_mlx *mlx, char *line);
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
void	ft_set_pos(t_mlx *mlx, char **map);

/*		ft_mlx_set.c		*/
void	window_init(t_mlx *mlx);
void	image_init(t_mlx *mlx);
void	draw_minimap(t_mlx *mlx);

/*		ft_set_map		*/
int		ft_find_longest_len(char **map);
int		ft_max_width(char **map);
void	ft_set_map(t_mlx *mlx);
// void    ft_put_space_in_first_and_last_array(t_mlx *mlx);
// void    ft_put_space_in_first_and_last_slot_of_array(t_mlx *mlx);
// void    ft_copy_map(t_mlx *mlx);
// void    ft_make_map_to_square(t_mlx *mlx);

/*		ft_draw_grid.c		*/
// void	ft_draw_rectagle(t_mlx *mlx, int x, int y, int color);
// void	ft_draw_grid(t_mlx *mlx, char val, int color);
// void	ft_draw_player(t_mlx *mlx, int color);

/*		ft_key_press.c		*/
int		ft_end_game(t_mlx *mlx);
// int		ft_is_wall(t_mlx *mlx, double px, double py);
// void	ft_remove_screen(t_mlx *mlx);
// void	ft_move(t_mlx *mlx, double theta);
void	ft_move(int keycode, t_mlx *mlx);
int		ft_key_press(int keycode, t_mlx *mlx);

/*		ft_draw_cam_plane.c		*/
// void    ft_draw_cam_plane(t_mlx *mlx);

/*		ft_rotate.c				*/
void	ft_rotate(int keycode, t_ray *ray);
// void    ft_rotate(t_mlx *mlx, double angle);

// /*		ft_draw_line.c		*/
// void 	ft_draw_line_1(t_mlx *mlx, double y[2], double m);
// void 	ft_draw_line_2(t_mlx *mlx, double y[2], double m);
// void 	ft_draw_line_3(t_mlx *mlx, double x[2], double y[2], double m);
// void	ft_draw_line_4(t_mlx *mlx, double x[2], double y[2], double m);
// void    ft_draw_line(t_mlx *mlx, double x[2], double y[2]);

/*		ft_draw_texture.c		*/
void    ft_distance(t_mlx *mlx);
void    ft_draw_cam_ray(t_mlx *mlx, double dir_x, double dir_y, int color);
// void    ft_draw_wall(t_mlx *mlx, double x);
void	ft_draw_wall(t_mlx *mlx, int x, int start, int end);
void	ft_draw_ceiling(t_mlx *mlx, int x, int wallstart, int color);
void	ft_draw_floor(t_mlx *mlx, int x, int wallend, int color);

/*		ft_img.c		*/
void	ft_init_texture(t_mlx *mlx);
void	ft_load_texture(t_mlx *mlx);

/*		ft_error.c		*/
void	ft_free_map(t_mlx *mlx);
void	ft_free_tmp(t_mlx *mlx);
void	ft_free_line(t_mlx *mlx);
void	ft_free_mlx(t_mlx *mlx);

/*		ft_raycast_algo.c		*/
void	ft_get_plane_vector(t_mlx *mlx);
void	ft_set_coordinate(t_ray *ray);
void	ft_set_dda(t_ray *ray);
void	ft_perform_dda(t_mlx *mlx, t_ray *ray);
void	ft_calcul_distance(t_ray *ray);

/*		ft_texture.c			*/
void	ft_get_wallX(t_ray *ray, t_mlx *mlx);
void	ft_get_walltexture(t_ray *ray, t_mlx *mlx, int x);
// void	ft_get_texture_color(t_ray *ray, t_img_data *img_data, int x, int y);
void	user_mlx_pixel_put(t_img_data *img, int x, int y, int color);


#endif
