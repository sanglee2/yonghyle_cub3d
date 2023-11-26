/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:54:51 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 19:56:11 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_get_dir_vector(t_mlx *mlx, char c)
{
	if (c == 'N')
	{
		mlx->ray.dir_y = 1;
		mlx->ray.plane_x = -0.66;
	}
	else if (c == 'S')
	{
		mlx->ray.dir_y = -1;
		mlx->ray.plane_x = 0.66;
	}
	if (c == 'W')
	{
		mlx->ray.dir_x = -1;
		mlx->ray.plane_y = -0.66;
	}
	if (c == 'E')
	{
		mlx->ray.dir_x = 1;
		mlx->ray.plane_y = 0.66;
	}
}

void	ft_find_player(t_mlx *mlx, int player, int x, int y)
{
	while (mlx->tmp[y])
	{
		x = 0;
		while (mlx->tmp[y][x])
		{
			if (mlx->tmp[y][x] == 'N' || mlx->tmp[y][x] == 'S' || \
					mlx->tmp[y][x] == 'W' || mlx->tmp[y][x] == 'E')
			{
				ft_get_dir_vector(mlx, mlx->tmp[y][x]);
				mlx->data.x = x;
				mlx->data.y = y;
				player++;
			}
			x++;
		}
		y++;
	}
	if (player != 1)
	{
		printf("player is not alone\n");
		ft_free_mlx(mlx);
	}
}

void	ft_is_valid_map(t_mlx *mlx)
{
	ft_set_map(mlx);
	ft_find_player(mlx, 0, 0, 0);
	check_map_is_closed(mlx->tmp, mlx);
}
