/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:52:52 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/23 15:50:15 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_end_game(t_mlx *mlx)
{
	printf("ft_end_game\n");
	mlx_destroy_window(mlx->mlx, mlx->mini);
	mlx_destroy_window(mlx->mlx, mlx->win);
	ft_free_map(mlx);
	ft_free_tmp(mlx);
	ft_free_line(mlx);
	exit(0);
}

// int	ft_is_wall(t_mlx *mlx, double px, double py)
// {
// 	double	angle;
// 	double	r;
// 	int		x;
// 	int		y;
// 	int		i;

// 	r = mlx->ray.radius;
// 	i = 0;
// 	while (i < 360)
// 	{
// 		angle = i * 2.0 * M_PI / 360;
// 		x = (int)(px + r * cos(angle)) / GRID_LEN;
// 		y = (int)(py + r * sin(angle)) / GRID_LEN;
// 		if (mlx->map[y][x] == '1')
// 			return (1);
// 		i += 10;
// 	}
// 	return (0);
// }

// void	ft_remove_screen(t_mlx *mlx)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < mlx->screenHeight)
// 	{
// 		j = -1;
// 		while (++j < mlx->screenWidth)
// 		{
// 			mlx_pixel_put(mlx->mlx, mlx->win, j, i, 0x000000);
// 			mlx_pixel_put(mlx->mlx, mlx->mini, j, i, 0x000000);
// 		}
// 	}
// }

// void	ft_move(t_mlx *mlx, double theta)
// {
// 	double	rx;
// 	double	ry;
// 	double	px;
// 	double	py;

// 	px = mlx->ray.pos_x;
// 	py = mlx->ray.pos_y;
// 	rx = mlx->ray.dir_x * cos(theta) - mlx->ray.dir_y * sin(theta);
// 	ry = mlx->ray.dir_x * sin(theta) + mlx->ray.dir_y * cos(theta);
// 	px += (int)(rx * 10);
// 	py += (int)(ry * 10);
	// if (ft_is_wall(mlx, px, py) == 1)
	// 	return ;
	// ft_remove_screen(mlx);
	// ft_draw_grid(mlx, '0', 0xFFFFFF);
	// ft_draw_grid(mlx, '1', 0xFF0000);
	// mlx->ray.pos_x = px;
	// mlx->ray.pos_y = py;
	// ft_draw_player(mlx, 0xFFFF00);
	// // ft_draw_cam_plane(mlx);
// }

void	ft_go_forward(t_mlx *mlx, t_ray *ray)
{
	if (mlx->map[(int)(ray->pos_y)][(int)(ray->pos_x + ray->dir_x * MOVE_RATIO * LIMITS)] == '0')
		ray->pos_x = ray->pos_x + ray->dir_x * MOVE_RATIO;
	if (mlx->map[(int)(ray->pos_y + ray->dir_y * MOVE_RATIO * LIMITS)][(int)(ray->pos_x)] == '0')
		ray->pos_y = ray->pos_y + ray->dir_y * MOVE_RATIO;
}

void	ft_go_backward(t_mlx *mlx, t_ray *ray)
{
	if (mlx->map[(int)(ray->pos_y)][(int)(ray->pos_x - ray->dir_x * MOVE_RATIO * LIMITS)] == '0')
		ray->pos_x = ray->pos_x - ray->dir_x * MOVE_RATIO;
	if (mlx->map[(int)(ray->pos_y - ray->dir_y * MOVE_RATIO * LIMITS)][(int)(ray->pos_x)] == '0')
		ray->pos_y = ray->pos_y - ray->dir_y * MOVE_RATIO;
}

void	ft_go_left(t_mlx *mlx, t_ray *ray)
{
	if (mlx->map[(int)(ray->pos_y)][(int)(ray->pos_x - ray->dir_y * MOVE_RATIO * LIMITS)] == '0') // 회전변환 양수 90인 걸 생각.
		ray->pos_x = ray->pos_x - ray->dir_y * MOVE_RATIO;
	if (mlx->map[(int)(ray->pos_y + ray->dir_x * MOVE_RATIO * LIMITS)][(int)(ray->pos_x)] == '0')
		ray->pos_y = ray->pos_y + ray->dir_x * MOVE_RATIO; // 직진을 해서 앞으로 나아갈 수 있음.
}

void	ft_go_right(t_mlx *mlx, t_ray *ray)
{
	if (mlx->map[(int)(ray->pos_y)][(int)(ray->pos_x + ray->dir_y * MOVE_RATIO * LIMITS)] == '0')
		ray->pos_x = ray->pos_x + ray->dir_y * MOVE_RATIO;
	if (mlx->map[(int)(ray->pos_y - ray->dir_x * MOVE_RATIO * LIMITS)][(int)(ray->pos_x)] == '0')
		ray->pos_y = ray->pos_y - ray->dir_x * MOVE_RATIO;
}

void	ft_move(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
		ft_go_forward(mlx, &mlx->ray);
	else if (keycode == KEY_A)
		ft_go_left(mlx, &mlx->ray);
	else if (keycode == KEY_S)
		ft_go_backward(mlx, &mlx->ray);
	else if (keycode == KEY_D)
		ft_go_right(mlx, &mlx->ray);
}

int	ft_key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		ft_end_game(mlx);
	else if (keycode == KEY_W || keycode == KEY_A \
			|| keycode == KEY_S || keycode == KEY_D)
			ft_move(keycode, mlx);
	else if (keycode == KEY_R || keycode == KEY_L)
		ft_rotate(keycode, &mlx->ray);
	return (0);	
}

// int	ft_key_press(int keycode, t_mlx *mlx)
// {
// 	if (keycode == 53)
// 		ft_end_game(mlx);
// 	else if (keycode != 0 && keycode != 1 && keycode != 2 && \
// 			keycode != 13 && keycode != 123 && keycode != 124)
// 		return (0);
// 	if (keycode == 0)
// 		ft_move(mlx, -M_PI / 2);
// 	else if (keycode == 1)
// 		ft_move(mlx, M_PI);
// 	else if (keycode == 2)
// 		ft_move(mlx, M_PI / 2);
// 	else if (keycode == 3)
// 		ft_move(mlx, 0);
// 	else if (keycode == 123)		// 18로 나눠서 처리해줌! + 그리고 - 나눠서 받음.
// 		ft_rotate(mlx, -M_PI / 18);
// 	else if (keycode == 124)
// 		ft_rotate(mlx, M_PI / 18);
// 	return (keycode);
// }


