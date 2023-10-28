/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_map_to_square.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:51:31 by jihokim2          #+#    #+#             */
/*   Updated: 2023/10/28 12:52:46 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_find_longest_len(char **map)
{
	int	max;
	int	len;
	int	y;

	max = 0;
	y = 0;
	while (map[y])
	{
		len = ft_linelen(map[y]);
		if (len > max)
			max = len;
		y++;
	}
	return (max);
}

void	ft_put_space_in_first_and_last_array(t_mlx *mlx)
{
	int	x;

	x = 0;
	while (x <= mlx->mapWidth)
	{
		mlx->tmp[0][x] = ' ';
		mlx->tmp[mlx->mapHeight + 1][x] = ' ';
		x++;
	}
}

void	ft_put_space_in_first_and_last_slot_of_array(t_mlx *mlx)
{
	int	y;

	y = 1;
	while (y <= mlx->mapHeight)
	{
		mlx->tmp[y][0] = ' ';
		mlx->tmp[y][mlx->mapWidth] = ' ';
		y++;
	}
}

void	ft_copy_map(t_mlx *mlx)
{
	int	flag;
	int	x;
	int	y;

	y = 0;
	while (y < mlx->mapHeight)
	{
		flag = 0;
		x = 0;
		while (x < mlx->mapWidth)
		{
			if (flag == 0)
				mlx->tmp[y + 1][x + 1] = mlx->map[y][x];
			if (mlx->map[y][x] == '\n' || mlx->map[y][x] == '\0')
				flag = 1;
			if (flag == 1)
				mlx->tmp[y + 1][x + 1] = ' ';
			x++;
		}
		y++;
	}
}

void	ft_make_map_to_square(t_mlx *mlx)
{
	int	i;

	mlx->mapHeight = ft_arrlen(mlx->map);
	if (mlx->mapHeight < 3)
		ft_free_mlx(mlx);
	mlx->mapWidth = ft_find_longest_len(mlx->map);
	if (mlx->mapWidth < 4)
		ft_free_mlx(mlx);
	mlx->tmp = (char **)ft_calloc(mlx, mlx->mapHeight + 3, sizeof(char *));
	i = -1;
	while (++i < mlx->mapHeight + 2)
		mlx->tmp[i] = (char *)ft_calloc(mlx, mlx->mapWidth + 2, sizeof(char));
	ft_put_space_in_first_and_last_array(mlx);
	ft_put_space_in_first_and_last_slot_of_array(mlx);
	ft_copy_map(mlx);
}
