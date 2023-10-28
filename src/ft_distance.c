/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_distance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:12:55 by jihokim2          #+#    #+#             */
/*   Updated: 2023/10/28 13:16:17 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_draw_cam_ray(t_mlx *mlx, double cam_x, double cam_y, int color)
{
	int	ray_x;
	int	ray_y;
	int	i;

	i = 1;
	while (1)
	{
		ray_x = cam_x + i * mlx->ray.dir_x;
		ray_y = cam_y + i * mlx->ray.dir_y;
		mlx_pixel_put(mlx->mlx, mlx->mini, ray_x, ray_y, color);
		if (mlx->map[ray_y / GRID_LEN][ray_x / GRID_LEN] == '1')
		{
			mlx->ddd.ray_x = ray_x;
			mlx->ddd.ray_y = ray_y;
			break ;
		}
		i++;
	}
}

void	ft_distance(t_mlx *mlx)
{
	double	dx;
	double	dy;

	dx = mlx->ddd.ray_x - mlx->ray.pos_x;
	dy = mlx->ddd.ray_y - mlx->ray.pos_y;
	mlx->ddd.d = sqrt(dx * dx + dy * dy);
	mlx->ddd.height = mlx->screenHeight * (1 - mlx->ddd.d / mlx->ddd.diagonal);
}

void	ft_draw_wall(t_mlx *mlx, double x)
{
	double	y;
	int		j;

	j = -1;
	while (++j <= mlx->ddd.height)
	{
		y = (mlx->screenHeight - mlx->ddd.height) / 2 + j;
		ft_pixel_put(mlx, x, y, j * 64 / mlx->ddd.height);
	}
}

void	ft_draw_ceiling(t_mlx *mlx, double x, int color)
{
	int	j;

	j = mlx->ddd.height / 2;
	while (++j <= mlx->screenHeight / 2)
		mlx_pixel_put(mlx->mlx, mlx->win, x, mlx->screenHeight / 2 + j, color);
}

void	ft_draw_floor(t_mlx *mlx, double x, int color)
{
	int	j;

	j = -mlx->screenHeight / 2 - 1;
	while (++j < -mlx->ddd.height / 2)
		mlx_pixel_put(mlx->mlx, mlx->win, x, mlx->screenHeight / 2 + j, color);
}
