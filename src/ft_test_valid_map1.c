/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_valid_map1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:00:29 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/26 20:02:35 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_map_is_closed(char **tmp, t_mlx *mlx)
{
	int	y;
	int	x;

	y = 0;
	while (y < mlx->map_height)
	{
		x = 0;
		while (x < mlx->map_width)
		{
			if (tmp[y][x] == '0' || tmp[y][x] == 'N' || \
				tmp[y][x] == 'S' || tmp[y][x] == 'E' || \
				tmp[y][x] == 'W')
				check_is_surrouned(tmp, y, x, mlx);
			++x;
		}
		++y;
	}
}

void	check_is_surrouned(char **tmp, int y, int x, t_mlx *mlx)
{
	check_north_is_empty(mlx, tmp, y, x);
	check_south_is_empty(mlx, tmp, y, x);
	check_east_is_empty(mlx, tmp, y, x);
	check_west_is_empty(mlx, tmp, y, x);
}
