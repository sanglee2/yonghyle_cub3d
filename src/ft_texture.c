/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:26:03 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/26 16:02:24 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_get_wallX(t_ray *ray, t_mlx *mlx)
{
	double wallX;


	if (ray->orthogonal == 0)
		wallX = ray->pos_y + (ray->plane_hitDist * ray->rdir_y);
	else
		wallX = ray->pos_x + (ray->plane_hitDist * ray->rdir_x);
	wallX = wallX - floor(wallX);
	if (ray->orthogonal == 0 && ray->rdir_x < 0)
		wallX = 1.0 - wallX;
	else if (ray->orthogonal == 1 && ray->rdir_y > 0)
		wallX = 1.0 - wallX;
	ray->tex_x = (int) (wallX * (double)TEXWIDTH);
	ray->wallheight = (int) (mlx->screenHeight / ray->plane_hitDist);
	ray->wallstart =  mlx->screenHeight / 2 - ray->wallheight / 2;
	ray->wallend = mlx->screenHeight / 2 + ray->wallheight / 2;
	if (ray->wallstart < 0)
		ray->wallstart = 0;
	if (ray->wallend >= mlx->screenHeight)
		ray->wallend = mlx->screenHeight;
	ray->ratio = 1.0 * TEXHEIGHT / ray->wallheight;
	ray->texpos = (ray->wallstart - mlx->screenHeight / 2 + ray->wallheight / 2 ) * ray->ratio;
}

void	user_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (img->length * y + x * img->bpp / 8);
	*(unsigned int *)dest = color;
}

void	ft_get_walltexture(t_ray *ray , t_mlx *mlx, int x)
{
	int	y;
	int j;
	int color;
	
	j = 0;
	y = ray->wallstart;
	while(y < ray->wallend)
	{
		if (ray->tex_x >= TEXWIDTH)
			ray->tex_x = TEXWIDTH - 1;
		if (ray->tex_y >= TEXHEIGHT)
			ray->tex_y = TEXHEIGHT - 1;
		ray->tex_y = (int)ray->texpos & (TEXHEIGHT - 1);
		if (ray->orthogonal == 0)
		{
			if (ray->rdir_x > 0)
			{
				color = *((unsigned int *) mlx->img_data[EA].addr + \
						ray->tex_y * TEXWIDTH + ray->tex_x);
			}
			else
			{
				color = *((unsigned int *) mlx->img_data[WE].addr + \
						ray->tex_y * TEXWIDTH + ray->tex_x);
			}
		}
		else if (ray->orthogonal == 1)
		{
			if (ray->rdir_y > 0)
			{
				color = *((unsigned int *) mlx->img_data[SO].addr + \
						ray->tex_y * TEXWIDTH + ray->tex_x);
			}
			else
			{
				color = *((unsigned int *) mlx->img_data[NO].addr + \
						ray->tex_y * TEXWIDTH + ray->tex_x);
			}
		}
		user_mlx_pixel_put(&mlx->img, x, y, color);	
		ray->texpos = ray->texpos + ray->ratio;
		y++;
		j++;
	}
}
