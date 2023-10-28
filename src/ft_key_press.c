/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:52:52 by jihokim2          #+#    #+#             */
/*   Updated: 2023/10/28 12:54:45 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_end_game(t_mlx *mlx)
{
	printf("ft_end_game\n");
	mlx_destroy_window(mlx->mlx, mlx->mini);
	mlx_destroy_window(mlx->mlx, mlx->win);
	ft_free_map(mlx);
	ft_free_tmp(mlx);
	ft_free_line(mlx);
	exit(0);
}

int	ft_is_wall(t_mlx *mlx, double px, double py)
{
	double	angle;
	double	r;
	int		x;
	int		y;
	int		i;

	r = mlx->ray.radius;
	i = 0;
	while (i < 360)
	{
		angle = i * 2.0 * M_PI / 360;
		x = (int)(px + r * cos(angle)) / GRID_LEN;
		y = (int)(py + r * sin(angle)) / GRID_LEN;
		if (mlx->map[y][x] == '1')
			return (1);
		i += 10;
	}
	return (0);
}

void	ft_remove_screen(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mlx->screenHeight)
	{
		j = -1;
		while (++j < mlx->screenWidth)
		{
			mlx_pixel_put(mlx->mlx, mlx->win, j, i, 0x000000);
			mlx_pixel_put(mlx->mlx, mlx->mini, j, i, 0x000000);
		}
	}
}

void	ft_move(t_mlx *mlx, double theta)
{
	double	rx;
	double	ry;
	double	px;
	double	py;

	px = mlx->ray.pos_x;
	py = mlx->ray.pos_y;
	rx = mlx->ray.dir_x * cos(theta) - mlx->ray.dir_y * sin(theta);
	ry = mlx->ray.dir_x * sin(theta) + mlx->ray.dir_y * cos(theta);
	px += (int)(rx * 10);
	py += (int)(ry * 10);
	if (ft_is_wall(mlx, px, py) == 1)
		return ;
	ft_remove_screen(mlx);
	ft_draw_grid(mlx, '0', 0xFFFFFF);
	ft_draw_grid(mlx, '1', 0xFF0000);
	mlx->ray.pos_x = px;
	mlx->ray.pos_y = py;
	ft_draw_player(mlx, 0xFFFF00);
	ft_draw_cam_plane(mlx);
}

int	ft_key_press(int keycode, t_mlx *mlx)
{
	if (keycode == 53)
		ft_end_game(mlx);
	else if (keycode != 0 && keycode != 1 && keycode != 2 && \
			keycode != 13 && keycode != 123 && keycode != 124)
		return (0);
	if (keycode == 0)
		ft_move(mlx, -M_PI / 2);
	else if (keycode == 1)
		ft_move(mlx, M_PI);
	else if (keycode == 2)
		ft_move(mlx, M_PI / 2);
	else if (keycode == 13)
		ft_move(mlx, 0);
	else if (keycode == 123)
		ft_rotate(mlx, -M_PI / 18);
	else if (keycode == 124)
		ft_rotate(mlx, M_PI / 18);
	return (keycode);
}
