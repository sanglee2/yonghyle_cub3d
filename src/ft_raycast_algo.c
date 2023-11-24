/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_algo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:05:14 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/23 21:03:05 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_get_plane_vector(t_mlx *mlx)
{
	mlx->ray.plane_x = -1 * mlx->ray.dir_y;
	mlx->ray.plane_y = -1 * mlx->ray.dir_x;
	// double plane_x = 0;
	// double plane_y = 1;
}

void	ft_set_coordinate(t_ray *ray)
{

	ray->mapX = (int)ray->pos_x;
	ray->mapY = (int)ray->pos_y;

	if (ray->rdir_x == 0) 
		ray->varDistY = 0; 
	else 
	{
		if (ray->rdir_y == 0)
			ray->varDistY = 1;
		else 
			ray->varDistY = fabs(1 / ray->rdir_y);
	}

	if (ray->rdir_y == 0)
		ray->varDistX = 0;
	else
	{
		if (ray->rdir_x == 0)
			ray->varDistX = 1;
		else
			ray->varDistX = fabs(1 / ray->rdir_x);
		
	}
}

void	ft_set_dda(t_ray *ray)                                            // 각 방향마다 이동할 거리 모두 구하기.	
{
	if (ray->rdir_x > 0)
	{
		ray->stepX = 1;
		ray->initDistX = ((ray->mapX + 1.0) - ray->pos_x) * ray->varDistX;	// 어떻게 점프해야 할 지 기술.
	}
	else
	{
		ray->stepX = -1;
		ray->initDistX = (ray->pos_x - ray->mapX) * ray->varDistX;
	}
	if (ray->rdir_y > 0)
	{
		ray->stepY = 1;
		ray->initDistY = ((ray->mapY + 1.0) - ray->pos_y) * ray->varDistY;
	}
	else
	{
		ray->stepY = -1;
		ray->initDistY = (ray->pos_y - ray->mapY) * ray->varDistY;
	}
	// 각 x격자, y격자 기준 이동거리.	
}

void	ft_perform_dda(t_mlx *mlx, t_ray *ray)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->initDistX < ray->initDistY)
		{
			ray->initDistX = ray->initDistX + ray->varDistX;
			ray->mapX = ray->mapX + ray->stepX;
			ray->orthogonal = 0;							// 직교인 벽면. x면에 맞음.
		}
		else
		{
			ray->initDistY = ray->initDistY + ray->varDistY;
			ray->mapY = ray->mapY + ray->stepY;
			ray->orthogonal = 1;						
		}
		if (mlx->map[ray->mapY][ray->mapX] == '1')						// map free 안하고 갖고 있어야 해.
		{
			hit = 1;
		}
	}
}

void	ft_calcul_distance(t_ray *ray)
{
	if (ray->orthogonal == 1)	// y벽면에 맞았다는 뜻
	{
		if (ray->stepY == 1)
			ray->plane_hitDist = (ray->mapY - ray->pos_y) / ray->rdir_y;
		else
			ray->plane_hitDist = (1 + ray->mapY - ray->pos_y) / ray->rdir_y;
	}
	else
	{
		if (ray->stepX == 1)
			ray->plane_hitDist = (ray->mapX - ray->pos_x) / ray->rdir_x;		// 광선 방향향벡벡터터의  x 성분만큼 나눠줘.
		else
			ray->plane_hitDist = (1 + ray->mapX - ray->pos_x) / ray->rdir_x;
	}
}