/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:11:49 by jihokim2          #+#    #+#             */
/*   Updated: 2023/10/28 13:12:50 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_draw_rectagle(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < GRID_LEN)
	{
		j = 0;
		while (j < GRID_LEN)
		{
			if (i == 0 || i == GRID_LEN - 1 || j == 0 || j == GRID_LEN - 1)
				mlx_pixel_put(mlx->mlx, mlx->mini, \
						x * GRID_LEN + j, y * GRID_LEN + i, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_grid(t_mlx *mlx, char val, int color)
{
	int	x;
	int	y;

	y = 0;
	while (mlx->map[y])
	{
		x = 0;
		while (mlx->map[y][x])
		{
			if (mlx->map[y][x] == val)
				ft_draw_rectagle(mlx, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_draw_player(t_mlx *mlx, int color)
{
	double	angle;
	double	r;
	double	x;
	double	y;
	int		i;

	r = mlx->ray.radius;
	x = mlx->ray.pos_x;
	y = mlx->ray.pos_y;
	i = 0;
	while (i < 360)
	{
		angle = i * 2.0 * M_PI / 360;
		mlx_pixel_put(mlx->mlx, mlx->mini, \
				x + r * cos(angle), y + r * sin(angle), color);
		i += 10;
	}
}
