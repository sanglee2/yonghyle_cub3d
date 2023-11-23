/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:51:31 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/20 13:11:06 by sanglee2         ###   ########.fr       */
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

// void	ft_put_space_in_first_and_last_array(t_mlx *mlx)		// 높이, 위 - 아래 whitespace로 둘러쳐 - 왜 그래야 함.	
// {
// 	int	x;

// 	x = 0;
// 	while (x <= mlx->mapWidth)
// 	{
// 		mlx->tmp[0][x] = ' ';
// 		mlx->tmp[mlx->mapHeight + 1][x] = ' ';
// 		x++;
// 	}
// }

// void	ft_put_space_in_first_and_last_slot_of_array(t_mlx *mlx) 	// 행의 첫번째, 마지막 끝 whitespace로 둘려쳐 - 왜 그래야 함.
// {
// 	int	y;

// 	y = 1;
// 	while (y <= mlx->mapHeight)
// 	{
// 		mlx->tmp[y][0] = ' ';
// 		mlx->tmp[y][mlx->mapWidth] = ' ';
// 		y++;
// 	}
// }

// void	ft_copy_map(t_mlx *mlx)
// {
// 	int	flag;
// 	int	x;
// 	int	y;

// 	y = 0;



// 	while (y < mlx->mapHeight)
// 	{
// 		flag = 0;
// 		x = 0;
// 		while (x < mlx->mapWidth)
// 		{
// 			if (flag == 0)
// 			{
// 				mlx->tmp[y + 1][x + 1] = mlx->map[y][x];
// 			}
// 			// printf("map : %c\n", mlx->map[y][x]);
// 			if (mlx->map[y][x] == '\n' || mlx->map[y][x] == '\0')
// 				flag = 1;
// 			if (flag == 1)
// 				mlx->tmp[y + 1][x + 1] = ' ';
// 			printf("%c", mlx->tmp[y + 1][x + 1]);
// 			x++;
// 		}
// 		printf("\n");
// 		printf("x: %d\n  y: %d\n", x, y);
// 		y++;
// 	}
// }

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

	// i = 0;

	// while(mlx->map[i])
	// {
	// 	printf("map놈들 : %s\n", mlx->map[i]);
	// 	i++;
	// }

	i = 0;
	mlx->mapHeight = ft_arrlen(mlx->map);
	mlx->mapWidth = ft_max_width(mlx->map);

	if (mlx->mapHeight < 3 || mlx->mapWidth < 4)      // 3줄 이상은 무조건 있어야 맵 완성.			
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

	// i = 0;
	// while(mlx->tmp[i])
	// {
	// 	printf("map들 : %s\n", mlx->tmp[i]);
	// 	i++;
	// }
}



// void	ft_make_map_to_square(t_mlx *mlx)
// {
// 	int	i;

// 	i = 0;
// 	mlx->mapHeight = ft_arrlen(mlx->map);
// 	if (mlx->mapHeight < 3)				// 3줄 이상은 무조건 있어야 맵 완성.
// 		ft_free_mlx(mlx);
// 	mlx->mapWidth = ft_find_longest_len(mlx->map);
// 	if (mlx->mapWidth < 4)				// 3개가 아닌 한 번 이동할 수 있는 4개를 준 이유.
// 		ft_free_mlx(mlx);
// 	mlx->tmp = (char **)ft_calloc(mlx, mlx->mapHeight + 35, sizeof(char *));
// 	i = -1;
// 	while (++i < mlx->mapHeight + 32)
// 		mlx->tmp[i] = (char *)ft_calloc(mlx, mlx->mapWidth + 35, sizeof(char));
// 	ft_put_space_in_first_and_last_array(mlx);
// 	ft_put_space_in_first_and_last_slot_of_array(mlx);
// 	ft_copy_map(mlx);

// }