/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_cam_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:05:17 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/15 16:07:23 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_draw_cam_plane(t_mlx *mlx)		// 카메라평면(직선) 그리는 함수.
{
	double	x[2];
	double	y[2];
	double	len;

	len = GRID_LEN;
	x[0] = mlx->ray.pos_x + \
		len * (mlx->ray.dir_x * cos(M_PI / 2) - mlx->ray.dir_y * sin(M_PI / 2));
	y[0] = mlx->ray.pos_y + \
		len * (mlx->ray.dir_x * sin(M_PI / 2) + mlx->ray.dir_y * cos(M_PI / 2));
	x[1] = mlx->ray.pos_x + \
	len * (mlx->ray.dir_x * cos(-M_PI / 2) - mlx->ray.dir_y * sin(-M_PI / 2));
	y[1] = mlx->ray.pos_y + \
	len * (mlx->ray.dir_x * sin(-M_PI / 2) + mlx->ray.dir_y * cos(-M_PI / 2));			// 카메라 평면 어떻게 구한건지 상세히 뜯어보기.
	ft_draw_line(mlx, x, y);
}



