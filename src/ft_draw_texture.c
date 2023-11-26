/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:12:55 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 15:50:51 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_draw_ceiling(t_mlx *mlx, int x, int wallstart, int color)
{
	int	y;

	y = -1;
	while (++y < wallstart) {
		user_mlx_pixel_put(&mlx->img, x, y, color);
	}
}

void	ft_draw_floor(t_mlx *mlx, int x, int wallend, int color)
{
	int	y;

	y = wallend - 1;
	while (++y < mlx->screenHeight)
		user_mlx_pixel_put(&mlx->img, x, y, color);
}
