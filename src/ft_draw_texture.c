/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:12:55 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/25 18:25:51 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void ft_draw_wall(t_mlx *mlx, int x, int start, int end)
// {
// 	int pixel_y;
// 	int color;

// 	color = 0x0000FF;

// 	pixel_y = start;
// 	while(pixel_y < end)
// 	{
// 		// mlx_pixel_put을 잘 쓸 것.
// 		user_mlx_pixel_put(&mlx->img, x, pixel_y, color);
// 		// mlx->data.addr[x + (pixel_y) * mlx->screenWidth] = color; // data.addr을 어떻게 초기화. 초기화 하는지.
// 		pixel_y++;
// 	}
// }

void	ft_draw_ceiling(t_mlx *mlx, int x, int wallstart, int color)
{
	int	y;

	y = -1;
	while (++y < wallstart) {
		user_mlx_pixel_put(&mlx->img, x, y, color);
	}
		// mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);
}

void	ft_draw_floor(t_mlx *mlx, int x, int wallend, int color)
{
	int	y;

	y = wallend - 1;
	while (++y < mlx->screenHeight)
		user_mlx_pixel_put(&mlx->img, x, y, color);
		// mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);
}
