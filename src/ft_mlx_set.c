/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:02:56 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/26 18:22:33 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	window_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx_do_key_autorepeaton(mlx->mlx);
	mlx->screen_height = 720;
	mlx->screen_width = 1080;
	mlx->win = mlx_new_window(mlx->mlx, mlx->screen_width, \
								mlx->screen_height, "cub3D");
}

void	image_init(t_mlx *mlx)
{
	ft_init_texture(mlx);
	ft_load_texture(mlx);
}
