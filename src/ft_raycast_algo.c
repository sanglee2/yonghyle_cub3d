/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_algo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:05:14 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/26 20:18:22 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_set_coordinate(t_ray *ray)
{
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	ray->vardist_y = fabs(1 / ray->rdir_y);
	ray->vardist_x = fabs(1 / ray->rdir_x);
}

void	ft_set_dda(t_ray *ray)
{
	if (ray->rdir_x > 0)
	{
		ray->step_x = 1;
		ray->initdist_x = ((ray->map_x + 1.0) - ray->pos_x) * ray->vardist_x;
	}
	else
	{
		ray->step_x = -1;
		ray->initdist_x = (ray->pos_x - ray->map_x) * ray->vardist_x;
	}
	if (ray->rdir_y > 0)
	{
		ray->step_y = 1;
		ray->initdist_y = ((ray->map_y + 1.0) - ray->pos_y) * ray->vardist_y;
	}
	else
	{
		ray->step_y = -1;
		ray->initdist_y = (ray->pos_y - ray->map_y) * ray->vardist_y;
	}
}

void	ft_perform_dda(t_mlx *mlx, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->initdist_x < ray->initdist_y)
		{
			ray->initdist_x = ray->initdist_x + ray->vardist_x;
			ray->map_x = ray->map_x + ray->step_x;
			ray->orthogonal = 0;
		}
		else
		{
			ray->initdist_y = ray->initdist_y + ray->vardist_y;
			ray->map_y = ray->map_y + ray->step_y;
			ray->orthogonal = 1;
		}
		if (mlx->map[ray->map_y][ray->map_x] == '1')
		{
			hit = 1;
		}
	}
}

void	ft_calcul_distance(t_ray *ray)
{
	if (ray->orthogonal == 1)
	{
		ray->plane_hitdist = \
			(ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->rdir_y;
	}
	else
	{
		ray->plane_hitdist = \
			(ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->rdir_x;
	}
}

void	ft_draw_vertical_line(t_mlx *mlx, int x)
{
	int		wallheight;
	int		wallstart;
	int		wallend;
	double	camera_x;

	camera_x = (2 * x / (double)mlx->screen_width) - 1;
	mlx->ray.rdir_x = mlx->ray.dir_x + (mlx->ray.plane_x * camera_x);
	mlx->ray.rdir_y = mlx->ray.dir_y + (mlx->ray.plane_y * camera_x);
	ft_set_coordinate(&mlx->ray);
	ft_set_dda(&mlx->ray);
	ft_perform_dda(mlx, &mlx->ray);
	ft_calcul_distance(&mlx->ray);
	wallheight = (int)(mlx->screen_height / mlx->ray.plane_hitdist);
	wallstart = (int)((mlx->screen_height / 2) - (wallheight / 2));
	wallend = (int)((mlx->screen_height / 2) + (wallheight / 2));
	ft_draw_ceiling(mlx, x, wallstart, mlx->data.intceiling);
	ft_draw_floor(mlx, x, wallend, mlx->data.intfloor);
	ft_get_wall_x(&mlx->ray, mlx);
	ft_get_walltexture(&mlx->ray, mlx, x);
}
