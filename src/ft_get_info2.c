/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:59:20 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 17:32:21 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_get_texture(t_mlx *mlx)
{
	if (mlx->data.information[0] == NULL)
		return ;
	ft_check_texture_element(mlx, &mlx->data);
	set_texture_element(mlx, &mlx->data);
}

void	ft_str_to_int(t_mlx *mlx, char *str)
{
	while (*str != ',')
	{
		mlx->data.R = mlx->data.R * 10 + (*str - '0');
		str++;
	}
	str++;
	while (*str != ',')
	{
		mlx->data.G = mlx->data.G * 10 + (*str - '0');
		str++;
	}
	str++;
	while (*str != '\0')
	{
		mlx->data.B = mlx->data.B * 10 + (*str - '0');
		str++;
	}
	if (mlx->data.R > 255 || mlx->data.R < 0 || \
		mlx->data.G > 255 || mlx->data.G < 0 || \
		mlx->data.B > 255 || mlx->data.B < 0)
	{
		printf("Wrong RGB value\n");
		ft_free_mlx(mlx);
	}
}

int	ft_edit_color(t_mlx *mlx, char *str)
{
	if (str == NULL)
	{	
		printf("none RGB value\n");
		ft_free_mlx(mlx);
	}
	ft_syntax_of_color(mlx, str);
	mlx->data.R = 0;
	mlx->data.G = 0;
	mlx->data.B = 0;
	ft_str_to_int(mlx, str);
	return ((mlx->data.R << 16) | (mlx->data.G << 8) | mlx->data.B);
}

void	ft_get_info(t_mlx *mlx)
{
	while (1)
	{
		mlx->data.line = get_next_line(mlx->data.fd);
		if (mlx->data.line == NULL)
			break ;
		mlx->data.information = ft_split(mlx->data.line);
		ft_get_texture(mlx);
		ft_free_info(&mlx->data);
		ft_free_line(mlx);
		mlx->data.line = NULL;
		if (mlx->data.north && mlx->data.south && mlx->data.west && \
			mlx->data.east && mlx->data.floor && mlx->data.ceiling)
			break ;
	}
	mlx->data.intfloor = ft_edit_color(mlx, mlx->data.floor);
	mlx->data.intceiling = ft_edit_color(mlx, mlx->data.ceiling);
}
