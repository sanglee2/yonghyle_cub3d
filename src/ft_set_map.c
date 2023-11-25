/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:51:31 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/25 22:18:01 by sanglee2         ###   ########.fr       */
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

int		ft_max_width(char **map)
{
	int max_width;
	int	length;
	int height;

	max_width = 0;
	height = 0;
	while(map[height])
	{
		length = ft_linelen(map[height]);
		if (length > max_width)
			max_width = length;
		height++;
	}
	return (max_width);	
}


void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*arr;
	size_t			i;

	arr = (unsigned char *)ptr;
	i = 0;
	while (i < num)
	{
		arr[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}


void	ft_set_map(t_mlx *mlx)
{
	int 	i;

	i = 0;
	mlx->mapHeight = ft_arrlen(mlx->map);
	mlx->mapWidth = ft_max_width(mlx->map);

	if (mlx->mapHeight < 3 || mlx->mapWidth < 3)      // 3줄 이상은 무조건 있어야 맵 완성.			
		ft_free_mlx(mlx);
	mlx->tmp = (char **)ft_calloc(mlx, mlx->mapHeight + 1, sizeof(char *));
	while(i < mlx->mapHeight)
	{
		mlx->tmp[i] = (char *)ft_calloc(mlx, mlx->mapWidth + 1, sizeof(char));
		ft_memset(mlx->tmp[i], ' ', mlx->mapWidth);
		mlx->tmp[i][mlx->mapWidth] = '\0';			// 굳이  필요없없는  구구문문.
		ft_strcpy(mlx->tmp[i], mlx->map[i]);		// NULL 일 때 copy 잘 되는지 봐야지.
		i++;
	}
}
