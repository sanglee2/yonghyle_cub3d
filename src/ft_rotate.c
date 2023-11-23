/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:13:18 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/23 10:56:20 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_rotate(int keycode, t_ray *ray)			// key_hook에서 잡고, 다시 그릴 때 언제 필요하느냐
{
	double prev_dir_x;
	double prev_plane_x;

	// double a = sin(90 * M_PI / 180); // sin, cos 함수들이 값은 모두 rad값임.
	// printf("degree : %f\n", a);

	if (keycode == KEY_L)
	{
		prev_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-1 * ROT_RATIO * M_PI / 180) - ray->dir_y * sin(-1 * ROT_RATIO * M_PI / 180);
		ray->dir_y = prev_dir_x * sin(-1 * ROT_RATIO * M_PI / 180) + ray->dir_y * cos(-1 * ROT_RATIO * M_PI / 180); 

		prev_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-1 * ROT_RATIO * M_PI / 180) - ray->plane_y * sin(-1 * ROT_RATIO * M_PI / 180);
		ray->plane_y = prev_plane_x * sin(-1 * ROT_RATIO * M_PI / 180) + ray->plane_y * cos(-1 * ROT_RATIO * M_PI / 180); 
	}	

	else if (keycode == KEY_R)
	{
		prev_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(ROT_RATIO * M_PI / 180) - ray->dir_y * sin(ROT_RATIO * M_PI / 180);
		ray->dir_y = prev_dir_x * sin(ROT_RATIO * M_PI / 180) + ray->dir_y * cos(ROT_RATIO * M_PI / 180); 

		prev_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(ROT_RATIO * M_PI / 180) - ray->plane_y * sin(ROT_RATIO * M_PI / 180);
		ray->plane_y = prev_plane_x * sin(ROT_RATIO * M_PI / 180) + ray->plane_y * cos(ROT_RATIO * M_PI / 180);
	}
}

// void	ft_rotate(t_mlx *mlx, double angle)
// {
// 	double	rx;
// 	double	ry;

// 	rx = mlx->ray.dir_x * cos(angle) - mlx->ray.dir_y * sin(angle);
// 	ry = mlx->ray.dir_x * sin(angle) + mlx->ray.dir_y * cos(angle);
// 	ft_remove_screen(mlx);
// 	ft_draw_grid(mlx, '0', 0xFFFFFF);
// 	ft_draw_grid(mlx, '1', 0xFF0000);
// 	mlx->ray.dir_x = rx;
// 	mlx->ray.dir_y = ry;
// 	ft_draw_player(mlx, 0xFFFF00);
// 	// ft_draw_cam_plane(mlx);
// }
