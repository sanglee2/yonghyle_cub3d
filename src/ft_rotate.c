/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:13:18 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/26 15:57:44 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_rotate(int keycode, t_ray *ray)
{
	double prev_dir_x;
	double prev_plane_x;

	if (keycode == KEY_L)
	{
		prev_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-1 * ROT_RATIO * M_PI / 180) - ray->dir_y * sin(-1 * ROT_RATIO * M_PI / 180);
		ray->dir_y = prev_dir_x * sin(-1 * ROT_RATIO * M_PI / 180) + ray->dir_y * cos(-1 * ROT_RATIO * M_PI / 180); 

		prev_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-1 * ROT_RATIO * M_PI / 180) - ray->plane_y * sin(-1 * ROT_RATIO * M_PI / 180);
		ray->plane_y = prev_plane_x * sin(-1 * ROT_RATIO * M_PI / 180) + ray->plane_y * cos(-1 * ROT_RATIO * M_PI / 180); 
	}	

	else if (keycode == KEY_R)
	{
		prev_dir_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(ROT_RATIO * M_PI / 180) - ray->dir_y * sin(ROT_RATIO * M_PI / 180);
		ray->dir_y = prev_dir_x * sin(ROT_RATIO * M_PI / 180) + ray->dir_y * cos(ROT_RATIO * M_PI / 180); 

		prev_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(ROT_RATIO * M_PI / 180) - ray->plane_y * sin(ROT_RATIO * M_PI / 180);
		ray->plane_y = prev_plane_x * sin(ROT_RATIO * M_PI / 180) + ray->plane_y * cos(ROT_RATIO * M_PI / 180);
	}
}
