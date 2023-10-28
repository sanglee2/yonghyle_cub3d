/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:41:07 by jihokim2          #+#    #+#             */
/*   Updated: 2023/10/28 12:44:58 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_pixel_put(t_mlx *mlx, double x, double y, int tex_y)
{
	int				dir;
	int				color;
	int				tex_x;
	unsigned int	*addr;

	dir = ft_get_dir(mlx);
	addr = (unsigned int *)mlx->img.addr[dir];
	if (dir == 0 || dir == 1)
		tex_x = (int)mlx->ddd.ray_y % GRID_LEN * 64 / GRID_LEN;
	else
		tex_x = (int)mlx->ddd.ray_x % GRID_LEN * 64 / GRID_LEN;
	color = *(addr + tex_y * 64 + tex_x);
	mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);
}

int	ft_get_dir(t_mlx *mlx)
{
	if ((int)mlx->ddd.ray_x % GRID_LEN == GRID_LEN - 1)
		return (0);
	else if ((int)mlx->ddd.ray_x % GRID_LEN == 0)
		return (1);
	else if ((int)mlx->ddd.ray_y % GRID_LEN == GRID_LEN - 1)
		return (2);
	else if ((int)mlx->ddd.ray_y % GRID_LEN == 0)
		return (3);
	return (0);
}
