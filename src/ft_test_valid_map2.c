/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_valid_map2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:00:29 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/26 20:03:27 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_empty_space(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	check_north_is_empty(t_mlx *mlx, char **tmp, int y, int x)
{
	if (y - 1 < 0)
	{
		printf("1tmp must be closed by wall\n");
		ft_free_mlx(mlx);
	}
	else if (y - 1 >= 0 && (is_empty_space(tmp[y - 1][x]) == FALSE \
							&& tmp[y - 1][x] != '1'))
	{
		printf("2tmp must be closed by wall\n");
		ft_free_mlx(mlx);
	}
	return ;
}

void	check_south_is_empty(t_mlx *mlx, char **tmp, int y, int x)
{
	if (y + 1 >= mlx->map_height)
	{
		printf("3tmp must be closed by wall\n");
		ft_free_mlx(mlx);
	}
	else if (is_empty_space(tmp[y + 1][x]) == FALSE && tmp[y + 1][x] != '1')
	{
		printf("4tmp must be closed by wall\n");
		ft_free_mlx(mlx);
	}
	return ;
}

void	check_east_is_empty(t_mlx *mlx, char **tmp, int y, int x)
{
	if (x + 1 >= mlx->map_width)
	{
		printf("5tmp must be closed by wall\n");
		ft_free_mlx(mlx);
	}
	else if (is_empty_space(tmp[y][x + 1]) == FALSE && tmp[y][x + 1] != '1')
	{
		printf("6tmp must be closed by wall\n");
		ft_free_mlx(mlx);
	}
	return ;
}

void	check_west_is_empty(t_mlx *mlx, char **tmp, int y, int x)
{
	if (x - 1 < 0)
	{
		printf("7tmp must be closed by wall\n");
		ft_free_mlx(mlx);
	}
	else if (is_empty_space(tmp[y][x - 1]) == FALSE && tmp[y][x - 1] != '1')
	{
		printf("8tmp must be closed by wall\n");
		ft_free_mlx(mlx);
	}
	return ;
}
