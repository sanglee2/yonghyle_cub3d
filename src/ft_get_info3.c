/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:59:20 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 17:52:03 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_num_true(t_mlx *mlx)
{
	if (mlx->color.num_flag == 0)
	{
		mlx->color.element++;
		mlx->color.num_flag = 1;
	}
	mlx->color.serial_comma = 0;
}

void	ft_serial_comma_zero(t_mlx *mlx)
{
	if (mlx->color.comma == 2)
	{
		printf("ft_syntax_of_serial_comma\n");
		ft_free_mlx(mlx);
	}
	mlx->color.serial_comma++;
	mlx->color.comma++;
	mlx->color.num_flag = 0;
}

void	ft_syntax_of_color(t_mlx *mlx, char *str)
{
	ft_bzero(&mlx->color, sizeof(mlx->color));
	while (*str != '\0')
	{
		if (ft_is_num(*str) == TRUE)
			ft_num_true(mlx);
		else if (*str == ',' && mlx->color.serial_comma == 0)
			ft_serial_comma_zero(mlx);
		else
		{
			printf("ft_syntax_of_white_space");
			ft_free_mlx(mlx);
		}
		str++;
	}
	if (mlx->color.element > 3 || mlx->color.comma != 2)
	{
		printf("ft_check_element_comma\n");
		ft_free_mlx(mlx);
	}
}
