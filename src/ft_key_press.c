/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:52:52 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/25 04:16:35 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_end_game(t_mlx *mlx)
{
	printf("ft_end_game\n");
	// mlx_destroy_window(mlx->mlx, mlx->mini);
	mlx_destroy_window(mlx->mlx, mlx->win);
	ft_free_map(mlx);
	ft_free_tmp(mlx);
	ft_free_line(mlx);
	exit(0);
}

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
	if (mlx->map[(int)(ray->pos_y)][(int)(ray->pos_x + ray->dir_y * MOVE_RATIO * LIMITS)] == '0') // 회전변환 양수 90인 걸 생각.
		ray->pos_x = ray->pos_x + ray->dir_y * MOVE_RATIO;
	if (mlx->map[(int)(ray->pos_y - ray->dir_x * MOVE_RATIO * LIMITS)][(int)(ray->pos_x)] == '0')
		ray->pos_y = ray->pos_y - ray->dir_x * MOVE_RATIO; // 직진을 해서 앞으로 나아갈 수 있음.
}

void	ft_go_right(t_mlx *mlx, t_ray *ray)
{
	if (mlx->map[(int)(ray->pos_y)][(int)(ray->pos_x - ray->dir_y * MOVE_RATIO * LIMITS)] == '0')
		ray->pos_x = ray->pos_x - ray->dir_y * MOVE_RATIO;
	if (mlx->map[(int)(ray->pos_y + ray->dir_x * MOVE_RATIO * LIMITS)][(int)(ray->pos_x)] == '0')
		ray->pos_y = ray->pos_y + ray->dir_x * MOVE_RATIO;
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



