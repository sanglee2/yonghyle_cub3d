/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:05:17 by jihokim2          #+#    #+#             */
/*   Updated: 2023/10/28 13:07:29 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_draw_cam_plane(t_mlx *mlx)
{
	double	x[2];
	double	y[2];
	double	len;

	len = mlx->ray.cam_plane_len;
	x[0] = mlx->ray.pos_x + \
		len * (mlx->ray.dir_x * cos(M_PI / 2) - mlx->ray.dir_y * sin(M_PI / 2));
	y[0] = mlx->ray.pos_y + \
		len * (mlx->ray.dir_x * sin(M_PI / 2) + mlx->ray.dir_y * cos(M_PI / 2));
	x[1] = mlx->ray.pos_x + \
	len * (mlx->ray.dir_x * cos(-M_PI / 2) - mlx->ray.dir_y * sin(-M_PI / 2));
	y[1] = mlx->ray.pos_y + \
	len * (mlx->ray.dir_x * sin(-M_PI / 2) + mlx->ray.dir_y * cos(-M_PI / 2));
	ft_draw_line(mlx, x, y);
}

void	ft_rotate(t_mlx *mlx, double angle)
{
	double	rx;
	double	ry;

	rx = mlx->ray.dir_x * cos(angle) - mlx->ray.dir_y * sin(angle);
	ry = mlx->ray.dir_x * sin(angle) + mlx->ray.dir_y * cos(angle);
	ft_remove_screen(mlx);
	ft_draw_grid(mlx, '0', 0xFFFFFF);
	ft_draw_grid(mlx, '1', 0xFF0000);
	mlx->ray.dir_x = rx;
	mlx->ray.dir_y = ry;
	ft_draw_player(mlx, 0xFFFF00);
	ft_draw_cam_plane(mlx);
}
