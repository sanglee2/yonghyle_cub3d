/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:02:56 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/26 16:51:18 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	window_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx_do_key_autorepeaton(mlx->mlx);
	mlx->screenHeight = 720;
	mlx->screenWidth = 1080;
	mlx->win = mlx_new_window(mlx->mlx, mlx->screenWidth, \
								mlx->screenHeight, "cub3D");
}

void	image_init(t_mlx *mlx)
{
	ft_init_texture(mlx);
	ft_load_texture(mlx);
}
