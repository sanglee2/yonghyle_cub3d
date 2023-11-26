/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:52:52 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 17:32:13 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_end_game(t_mlx *mlx)
{
	printf("ft_end_game\n");
	mlx_destroy_window(mlx->mlx, mlx->win);
	ft_free_map(mlx);
	ft_free_tmp(mlx);
	ft_free_line(mlx);
	exit(0);
}

void	ft_go_forward(t_mlx *mlx, t_ray *ray)
{
	if (ray->dir_x > 0)
	{
		if (mlx->map[(int)(ray->pos_y)][(int)(ray->pos_x + ray->dir_x * M + 0.1)] != '1')
			ray->pos_x = ray->pos_x + ray->dir_x * M;
	}
	else if (ray->dir_x < 0)
	{
		if (mlx->map[(int)(ray->pos_y)][(int)(ray->pos_x + ray->dir_x * M - 0.1)] != '1')
			ray->pos_x = ray->pos_x + ray->dir_x * M;
	}
	if (ray->dir_y > 0)
	{	
		if (mlx->map[(int)(ray->pos_y + ray->dir_y * M + 0.1)][(int)(ray->pos_x)] != '1')
			ray->pos_y = ray->pos_y + ray->dir_y * M;
	}
	else if (ray->dir_y < 0)
	{
		if (mlx->map[(int)(ray->pos_y + ray->dir_y * M - 0.1)][(int)(ray->pos_x)] != '1')
			ray->pos_y = ray->pos_y + ray->dir_y * M;
	}
}

void	ft_go_backward(t_mlx *mlx, t_ray *ray)
{
	if (ray->dir_x > 0)
	{
		if (mlx->map[(int)(ray->pos_y)][(int)(ray->pos_x - ray->dir_x * M - 0.1)] != '1')
			ray->pos_x = ray->pos_x - ray->dir_x * M;
	}
	else if (ray->dir_x < 0)
	{
		if (mlx->map[(int)(ray->pos_y)][(int)(ray->pos_x - ray->dir_x * M + 0.1)] != '1')
			ray->pos_x = ray->pos_x - ray->dir_x * M;
	}
	if (ray->dir_y > 0)
	{
		if (mlx->map[(int)(ray->pos_y - ray->dir_y * M - 0.1)][(int)(ray->pos_x)] != '1')
		ray->pos_y = ray->pos_y - ray->dir_y * M;
	}
	else if (ray->dir_y < 0)
	{
		if (mlx->map[(int)(ray->pos_y - ray->dir_y * M + 0.1)][(int)(ray->pos_x)] != '1')
			ray->pos_y = ray->pos_y - ray->dir_y * M;
	}
}

void	ft_go_left(t_mlx *mlx, t_ray *ray)
{
	if (mlx->map[(int)(ray->pos_y)][(int)(ray->pos_x + ray->dir_y * M)] != '1')
		ray->pos_x = ray->pos_x + ray->dir_y * M;
	if (mlx->map[(int)(ray->pos_y - ray->dir_x * M)][(int)(ray->pos_x)] != '1')
		ray->pos_y = ray->pos_y - ray->dir_x * M;
}

void	ft_go_right(t_mlx *mlx, t_ray *ray)
{
	if (mlx->map[(int)(ray->pos_y)][(int)(ray->pos_x - ray->dir_y * M)] != '1')
		ray->pos_x = ray->pos_x - ray->dir_y * M;
	if (mlx->map[(int)(ray->pos_y + ray->dir_x * M)][(int)(ray->pos_x)] != '1')
		ray->pos_y = ray->pos_y + ray->dir_x * M;
}
