/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:41:07 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/23 19:23:48 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	ft_pixel_put(t_mlx *mlx, double x, double y, int tex_y)
// {
// 	int				dir;
// 	int				color;
// 	int				tex_x;
// 	unsigned int	*addr;

// 	dir = ft_get_dir(mlx);
// 	addr = (unsigned int *)mlx->img.addr[dir];
// 	if (dir == 0 || dir == 1)
// 		tex_x = (int)mlx->ddd.ray_y % GRID_LEN * 64 / GRID_LEN;		// 이 수식의 명확성! - 여기에선 벗어나야 하는 거 맞지!
// 	else
// 		tex_x = (int)mlx->ddd.ray_x % GRID_LEN * 64 / GRID_LEN;
// 	color = *(addr + tex_y * 64 + tex_x);
// 	mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);
// }



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
