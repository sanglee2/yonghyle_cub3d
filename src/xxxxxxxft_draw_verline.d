/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_verline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 00:03:03 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/15 12:57:02 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void draw_verline(t_mlx *mlx, int x, int start, int end)
// {
// 	int pixel_y;
// 	int color;

// 	color = 0xFF0000;

// 	pixel_y = start;
// 	while(pixel_y <= end)
// 	{
// 		// mlx_pixel_put을 잘 쓸 것.
// 		mlx_pixel_put(mlx->mlx, mlx->win, x, start + pixel_y, color);
// 		// mlx->data.addr[x + (pixel_y) * mlx->screenWidth] = color; // data.addr을 어떻게 초기화. 초기화 하는지.
// 		pixel_y++;
// 	}
// }