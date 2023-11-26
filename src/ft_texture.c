/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 22:26:03 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/26 20:17:29 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_get_wall_x(t_ray *ray, t_mlx *mlx)
{
	double	wall_x;

	if (ray->orthogonal == 0)
		wall_x = ray->pos_y + (ray->plane_hitdist * ray->rdir_y);
	else
		wall_x = ray->pos_x + (ray->plane_hitdist * ray->rdir_x);
	wall_x = wall_x - floor(wall_x);
	if (ray->orthogonal == 0 && ray->rdir_x < 0)
		wall_x = 1.0 - wall_x;
	else if (ray->orthogonal == 1 && ray->rdir_y > 0)
		wall_x = 1.0 - wall_x;
	ray->tex_x = (int)(wall_x * (double)TEXWIDTH);
	ray->wallheight = (int)(mlx->screen_height / ray->plane_hitdist);
	ray->wallstart = mlx->screen_height / 2 - ray->wallheight / 2;
	ray->wallend = mlx->screen_height / 2 + ray->wallheight / 2;
	if (ray->wallstart < 0)
		ray->wallstart = 0;
	if (ray->wallend >= mlx->screen_height)
		ray->wallend = mlx->screen_height;
	ray->ratio = 1.0 * TEXHEIGHT / ray->wallheight;
	ray->texpos = (ray->wallstart - mlx->screen_height / 2 \
					+ ray->wallheight / 2) * ray->ratio;
}

void	user_mlx_pixel_put(t_img_data *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (img->length * y + x * img->bpp / 8);
	*(unsigned int *)dest = color;
}

void	ft_orthogonal_zero(t_ray *ray, t_mlx *mlx, int *color)
{
	if (ray->rdir_x > 0)
	{
		*color = *((unsigned int *) mlx->img_data[EA].addr + \
				ray->tex_y * TEXWIDTH + ray->tex_x);
	}
	else
	{
		*color = *((unsigned int *) mlx->img_data[WE].addr + \
				ray->tex_y * TEXWIDTH + ray->tex_x);
	}
}

void	ft_orthogonal_one(t_ray *ray, t_mlx *mlx, int *color)
{
	if (ray->rdir_y > 0)
	{
		*color = *((unsigned int *) mlx->img_data[SO].addr + \
				ray->tex_y * TEXWIDTH + ray->tex_x);
	}
	else
	{
		*color = *((unsigned int *) mlx->img_data[NO].addr + \
				ray->tex_y * TEXWIDTH + ray->tex_x);
	}
}

void	ft_get_walltexture(t_ray *ray, t_mlx *mlx, int x)
{
	int	y;
	int	color;

	y = ray->wallstart;
	while (y < ray->wallend)
	{
		if (ray->tex_x >= TEXWIDTH)
			ray->tex_x = TEXWIDTH - 1;
		if (ray->tex_y >= TEXHEIGHT)
			ray->tex_y = TEXHEIGHT - 1;
		ray->tex_y = (int)ray->texpos & (TEXHEIGHT - 1);
		if (ray->orthogonal == 0)
			ft_orthogonal_zero(ray, mlx, &color);
		else if (ray->orthogonal == 1)
			ft_orthogonal_one(ray, mlx, &color);
		user_mlx_pixel_put(&mlx->img, x, y, color);
		ray->texpos = ray->texpos + ray->ratio;
		y++;
	}
}
