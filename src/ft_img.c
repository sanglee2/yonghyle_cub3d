/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:56:28 by jihokim2          #+#    #+#             */
/*   Updated: 2023/10/28 12:57:44 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_mlx_xpm_file_to_image(t_mlx *mlx, int width, int height)
{
	mlx->img.img[0] = \
			mlx_xpm_file_to_image(mlx->mlx, mlx->data.north, &width, &height);
	mlx->img.img[1] = \
			mlx_xpm_file_to_image(mlx->mlx, mlx->data.south, &width, &height);
	mlx->img.img[2] = \
			mlx_xpm_file_to_image(mlx->mlx, mlx->data.west, &width, &height);
	mlx->img.img[3] = \
			mlx_xpm_file_to_image(mlx->mlx, mlx->data.east, &width, &height);
}

void	ft_mlx_get_data_addr(t_mlx *mlx, int bpp, int size, int endian)
{
	mlx->img.addr[0] = mlx_get_data_addr(mlx->img.img[0], &bpp, &size, &endian);
	mlx->img.addr[1] = mlx_get_data_addr(mlx->img.img[1], &bpp, &size, &endian);
	mlx->img.addr[2] = mlx_get_data_addr(mlx->img.img[2], &bpp, &size, &endian);
	mlx->img.addr[3] = mlx_get_data_addr(mlx->img.img[3], &bpp, &size, &endian);
}

void	ft_mlx_img(t_mlx *mlx)
{
	ft_mlx_xpm_file_to_image(mlx, 64, 64);
	ft_mlx_get_data_addr(mlx, 32, 256, 0);
}
