/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:41:07 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/23 21:02:36 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_get_dir(t_mlx *mlx)
{
	if ((int)mlx->ddd.ray_x % GRID_LEN == GRID_LEN - 1)
		return (0);
	else if ((int)mlx->ddd.ray_x % GRID_LEN == 0)
		return (1);
	else if ((int)mlx->ddd.ray_y % GRID_LEN == GRID_LEN - 1)
		return (2);
	else if ((int)mlx->ddd.ray_y % GRID_LEN == 0)
		return (3);
	return (0);
}
