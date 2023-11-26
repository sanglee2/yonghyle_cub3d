/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:56:28 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 15:53:23 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init_texture(t_mlx *mlx)
{
	mlx->img_data[NO].img = mlx_xpm_file_to_image(mlx->mlx, mlx->data.north, \
							&mlx->img_data[NO].width, &mlx->img_data[NO].height);
	mlx->img_data[SO].img = mlx_xpm_file_to_image(mlx->mlx, mlx->data.south, \
							&mlx->img_data[SO].width, &mlx->img_data[SO].height);
	mlx->img_data[WE].img = mlx_xpm_file_to_image(mlx->mlx, mlx->data.west, \
							&mlx->img_data[WE].width, &mlx->img_data[WE].height);
	mlx->img_data[EA].img = mlx_xpm_file_to_image(mlx->mlx, mlx->data.east, \
							&mlx->img_data[EA].width, &mlx->img_data[EA].height);
}

void	ft_load_texture(t_mlx *mlx)
{
	int i;

	i = 0;	
	while (i < 4)
	{
		mlx->img_data[i].addr = mlx_get_data_addr(mlx->img_data[i].img, \
								&mlx->img_data[i].bpp,\
								&mlx->img_data[i].length,\
								&mlx->img_data[i].endian);
		i++;
	}
}
