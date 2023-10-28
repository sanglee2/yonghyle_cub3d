/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:02:40 by jihokim2          #+#    #+#             */
/*   Updated: 2023/10/28 13:05:05 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_free_map(t_mlx *mlx)
{
	int	i;

	if (mlx->map)
	{
		i = 0;
		while (mlx->map[i])
		{
			free(mlx->map[i]);
			mlx->map[i] = NULL;
			i++;
		}
		free(mlx->map);
		mlx->map = NULL;
	}
}

void	ft_free_tmp(t_mlx *mlx)
{
	int	i;

	if (mlx->tmp)
	{
		i = 0;
		while (mlx->tmp[i])
		{
			free(mlx->tmp[i]);
			mlx->tmp[i] = NULL;
			i++;
		}
		free(mlx->tmp);
		mlx->tmp = NULL;
	}
}

void	ft_free_line(t_mlx *mlx)
{
	if (mlx->data.line)
	{
		free(mlx->data.line);
		mlx->data.line = NULL;
	}
}

void	ft_free_mlx(t_mlx *mlx)
{
	printf("\error\nft_free_mlx\n");
	ft_free_map(mlx);
	ft_free_tmp(mlx);
	ft_free_line(mlx);
	exit(1);
}
