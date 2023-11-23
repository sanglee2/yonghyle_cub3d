/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:07:46 by jihokim2          #+#    #+#             */
/*   Updated: 2023/10/28 13:11:44 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_draw_line_1(t_mlx *mlx, double y[2], double m)
{
	double	cam_x;
	double	cam_y;
	double	i;

	mlx->ddd.ratio = (y[1] - y[0]) / mlx->screenWidth;
	i = 0;
	while (i < mlx->screenWidth)
	{
		cam_y = y[0] + i * mlx->ddd.ratio;
		cam_x = (cam_y - mlx->ray.pos_y) * (-m) + mlx->ray.pos_x;
		mlx_pixel_put(mlx->mlx, mlx->mini, cam_x, cam_y, 0x00FF00);
		ft_draw_cam_ray(mlx, cam_x, cam_y, 0x00FF00);
		ft_distance(mlx);
		ft_draw_wall(mlx, mlx->screenWidth - (i + 1));
		ft_draw_ceiling(mlx, mlx->screenWidth - (i + 1), mlx->data.intceiling);
		ft_draw_floor(mlx, mlx->screenWidth - (i + 1), mlx->data.intfloor);
		i++;
	}
	cam_x = (cam_y - mlx->ray.pos_y) * m + mlx->ray.pos_x;
}

void	ft_draw_line_2(t_mlx *mlx, double y[2], double m)
{
	double	cam_x;
	double	cam_y;
	double	i;

	mlx->ddd.ratio = (y[0] - y[1]) / mlx->screenWidth;
	i = 0;
	while (i < mlx->screenWidth)
	{
		cam_y = y[1] + i * mlx->ddd.ratio;
		cam_x = (cam_y - mlx->ray.pos_y) * (-m) + mlx->ray.pos_x;
		mlx_pixel_put(mlx->mlx, mlx->mini, cam_x, cam_y, 0x00FF00);
		ft_draw_cam_ray(mlx, cam_x, cam_y, 0x00FF00);
		ft_distance(mlx);
		ft_draw_wall(mlx, (i + 1));
		ft_draw_ceiling(mlx, (i + 1), mlx->data.intceiling);
		ft_draw_floor(mlx, (i + 1), mlx->data.intfloor);
		i++;
	}
}

void	ft_draw_line_3(t_mlx *mlx, double x[2], double y[2], double m)
{
	double	cam_x;
	double	cam_y;
	double	i;

	mlx->ddd.ratio = (x[1] - x[0]) / mlx->screenWidth;
	i = 0;
	while (i < mlx->screenWidth)
	{
		cam_x = x[0] + i * mlx->ddd.ratio;
		cam_y = (cam_x - x[0]) / (-m) + y[0];
		mlx_pixel_put(mlx->mlx, mlx->mini, cam_x, cam_y, 0x00FF00);
		ft_draw_cam_ray(mlx, cam_x, cam_y, 0x00FF00);
		ft_distance(mlx);
		ft_draw_wall(mlx, mlx->screenWidth - (i + 1));
		ft_draw_ceiling(mlx, mlx->screenWidth - (i + 1), mlx->data.intceiling);
		ft_draw_floor(mlx, mlx->screenWidth - (i + 1), mlx->data.intfloor);
		i++;
	}
}

void	ft_draw_line_4(t_mlx *mlx, double x[2], double y[2], double m)
{
	double	cam_x;
	double	cam_y;
	double	i;

	mlx->ddd.ratio = (x[0] - x[1]) / mlx->screenWidth;
	i = -1;
	while (++i < mlx->screenWidth)
	{
		cam_x = x[1] + i * mlx->ddd.ratio;
		cam_y = (cam_x - x[0]) / (-m) + y[0];
		mlx_pixel_put(mlx->mlx, mlx->mini, cam_x, cam_y, 0x00FF00);
		ft_draw_cam_ray(mlx, cam_x, cam_y, 0x00FF00);
		ft_distance(mlx);
		ft_draw_wall(mlx, (i + 1));
		ft_draw_ceiling(mlx, (i + 1), mlx->data.intceiling);
		ft_draw_floor(mlx, (i + 1), mlx->data.intfloor);
	}
}

void	ft_draw_line(t_mlx *mlx, double x[2], double y[2])
{
	double	m;
	double	i;

	i = 0;
	m = mlx->ray.dir_y / mlx->ray.dir_x;
	if (m < 1 && m > -1)
	{
		if (y[0] < y[1])
			ft_draw_line_1(mlx, y, m);
		else
			ft_draw_line_2(mlx, y, m);
	}
	else
	{
		if (x[0] < x[1])
			ft_draw_line_3(mlx, x, y, m);
		else
			ft_draw_line_4(mlx, x, y, m);
	}
}
