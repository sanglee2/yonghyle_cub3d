/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:59:20 by jihokim2          #+#    #+#             */
/*   Updated: 2023/10/28 13:02:32 by jihokim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_get_texture(t_mlx *mlx, char *line)
{
	if (*line == '\0' || *line == '\n')
		return ;
	while (ft_is_space(*line) == TRUE)
		line++;
	if (*line == '\0')
		return ;
	else if (ft_strcmp(line, "NO ") == TRUE)
		mlx->data.north = ft_strcpy(mlx, line + 3);
	else if (ft_strcmp(line, "SO ") == TRUE)
		mlx->data.south = ft_strcpy(mlx, line + 3);
	else if (ft_strcmp(line, "WE ") == TRUE)
		mlx->data.west = ft_strcpy(mlx, line + 3);
	else if (ft_strcmp(line, "EA ") == TRUE)
		mlx->data.east = ft_strcpy(mlx, line + 3);
	else if (ft_strcmp(line, "F ") == TRUE)
		mlx->data.floor = ft_strcpy(mlx, line + 2);
	else if (ft_strcmp(line, "C ") == TRUE)
		mlx->data.ceiling = ft_strcpy(mlx, line + 2);
}

void	ft_syntax_of_color(t_mlx *mlx, char *str)
{
	int	num;
	int	comma;

	num = 0;
	comma = 0;
	while (*str)
	{
		if (*str == ',')
		{
			if (comma == 2 || num <= 0 || num >= 4)
				ft_free_mlx(mlx);
			comma++;
			num = 0;
		}
		else if (ft_is_num(*str) == TRUE)
			num++;
		else
			ft_free_mlx(mlx);
		str++;
	}
	if (num <= 0 || num >= 4 || comma != 2)
		ft_free_mlx(mlx);
}

void	ft_str_to_int(t_mlx *mlx, char *str)
{
	mlx->data.R = 0;
	while (*str != ',')
	{
		mlx->data.R = mlx->data.R * 10 + (*str - '0');
		str++;
	}
	str++;
	mlx->data.G = 0;
	while (*str != ',')
	{
		mlx->data.G = mlx->data.G * 10 + (*str - '0');
		str++;
	}
	str++;
	mlx->data.B = 0;
	while (*str != '\0')
	{
		mlx->data.B = mlx->data.B * 10 + (*str - '0');
		str++;
	}
}

int	ft_edit_color(t_mlx *mlx, char *str)
{
	if (str == NULL)
		ft_free_mlx(mlx);
	ft_syntax_of_color(mlx, str);
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
		ft_get_texture(mlx, mlx->data.line);
		ft_free_line(mlx);
		mlx->data.line = NULL;
		if (mlx->data.north && mlx->data.south && mlx->data.west && \
			mlx->data.east && mlx->data.floor && mlx->data.ceiling)
			break ;
	}
	mlx->data.intfloor = ft_edit_color(mlx, mlx->data.floor);
	mlx->data.intceiling = ft_edit_color(mlx, mlx->data.ceiling);
}
