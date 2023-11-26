/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_press2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:52:52 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 16:50:09 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_move(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_W)
		ft_go_forward(mlx, &mlx->ray);
	else if (keycode == KEY_A)
		ft_go_left(mlx, &mlx->ray);
	else if (keycode == KEY_S)
		ft_go_backward(mlx, &mlx->ray);
	else if (keycode == KEY_D)
		ft_go_right(mlx, &mlx->ray);
}

int	ft_key_press(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		ft_end_game(mlx);
	else if (keycode == KEY_W || keycode == KEY_A \
			|| keycode == KEY_S || keycode == KEY_D)
	{
		ft_move(keycode, mlx);
	}
	else if (keycode == KEY_R || keycode == KEY_L)
		ft_rotate(keycode, &mlx->ray);
	return (0);
}
