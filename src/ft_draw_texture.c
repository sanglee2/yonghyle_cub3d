/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:12:55 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/23 15:35:00 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	ft_draw_cam_ray(t_mlx *mlx, double cam_x, double cam_y, int color) // 광선 그리는 데 필요한 함수.
// {
// 	int	ray_x;
// 	int	ray_y;
// 	int	i;

// 	i = 1;
// 	while (1)
// 	{
// 		ray_x = cam_x + i * mlx->ray.dir_x;
// 		ray_y = cam_y + i * mlx->ray.dir_y;
// 		mlx_pixel_put(mlx->mlx, mlx->mini, ray_x, ray_y, color);
// 		if (mlx->map[ray_y / GRID_LEN][ray_x / GRID_LEN] == '1')
// 		{
// 			mlx->ddd.ray_x = ray_x;
// 			mlx->ddd.ray_y = ray_y;
// 			break ;
// 		}
// 		i++;
// 	}
// }

// void	ft_distance(t_mlx *mlx) // 벽까지 거리 & 벽 높이 구하기.
// {
// 	double	dx;
// 	double	dy;

// 	dx = mlx->ddd.ray_x - mlx->ray.pos_x;	// 광선의 x좌표 - 플레이어 x좌표.
// 	dy = mlx->ddd.ray_y - mlx->ray.pos_y;
// 	mlx->ddd.d = sqrt(dx * dx + dy * dy);	// 실제 벽까지의 거리.
// 	mlx->ddd.height = mlx->screenHeight * (1 - mlx->ddd.d / mlx->ddd.diagonal); // 벽 높이 구하기.
// }

void ft_draw_wall(t_mlx *mlx, int x, int start, int end)
{
	int pixel_y;
	int color;

	color = 0x0000FF;

	pixel_y = start;
	while(pixel_y <= end)
	{
		// mlx_pixel_put을 잘 쓸 것.
		mlx_pixel_put(mlx->mlx, mlx->win, x, pixel_y, color);
		// mlx->data.addr[x + (pixel_y) * mlx->screenWidth] = color; // data.addr을 어떻게 초기화. 초기화 하는지.
		pixel_y++;
	}
}

// void	ft_draw_wall(t_mlx *mlx, double x)
// {
// 	double	y;
// 	int		j;

// 	j = -1;
// 	while (++j <= mlx->ddd.height)
// 	{
// 		y = (mlx->screenHeight - mlx->ddd.height) / 2 + j;
// 		ft_pixel_put(mlx, x, y, j * 64 / mlx->ddd.height);	// 이게 무슨 함수?! - texture를 불러와야 하는데 상당히 까다로워짐.
// 	}
// }

void	ft_draw_ceiling(t_mlx *mlx, int x, int wallstart, int color)
{
	int	y;

	y = 0;
	while (++y <= wallstart)
		mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);
}

// void	ft_draw_ceiling(t_mlx *mlx, double x, int color)
// {
// 	int	j;

// 	j = mlx->ddd.height / 2;
// 	while (++j <= mlx->screenHeight / 2)
// 		mlx_pixel_put(mlx->mlx, mlx->win, x, mlx->screenHeight / 2 + j, color);
// }

void	ft_draw_floor(t_mlx *mlx, int x, int wallend, int color)
{
	int	y;

	y = wallend;
	while (++y <= mlx->screenHeight)
		mlx_pixel_put(mlx->mlx, mlx->win, x, y, color);
}

// void	ft_draw_floor(t_mlx *mlx, double x, int color)
// {
// 	int	j;

// 	j = -mlx->screenHeight / 2 - 1;
// 	while (++j < -mlx->ddd.height / 2)
// 		mlx_pixel_put(mlx->mlx, mlx->win, x, mlx->screenHeight / 2 + j, color);
// }
