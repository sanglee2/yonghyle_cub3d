/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:59:20 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 16:37:17 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_check_identifier(char *str)
{
	if (ft_strcmp(str, "NO") == TRUE)
		return (NO);
	else if (ft_strcmp(str, "SO") == TRUE)
		return (SO);
	else if (ft_strcmp(str, "WE") == TRUE)
		return (WE);
	else if (ft_strcmp(str, "EA") == TRUE)
		return (EA);
	else if (ft_strcmp(str, "F") == TRUE)
		return (FL);
	else if (ft_strcmp(str, "C") == TRUE)
		return (CE);
	else
		return (-1);
}

void	ft_check_texture_element(t_mlx *mlx, t_data *data)
{
	int	i;

	i = 0;
	if (ft_check_identifier(data->information[0]) == -1 || \
							data->information[1] == NULL || \
							data->information[2] != NULL)
	{
		while (data->information[i])
		{
			printf("information[%d] : %s\n", i, data->information[i]);
			i++;
		}
		printf("ft_check_texture_element\n");
		ft_free_mlx(mlx);
	}
}

int	ft_open_file(t_mlx *mlx, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("ft_open_file: ");
		ft_free_mlx(mlx);
	}
	return (fd);
}

void	ft_check_valid_path(t_mlx *mlx, int identifier, char *path)
{
	if (identifier == FL || identifier == CE)
		return ;
	if (ft_strcmp(mlx->data.north, path) == TRUE || \
		ft_strcmp(mlx->data.south, path) == TRUE || \
		ft_strcmp(mlx->data.west, path) == TRUE || \
		ft_strcmp(mlx->data.east, path) == TRUE)
	{
		printf("ft_check_valid_path\n");
		ft_free_mlx(mlx);
	}
	close(ft_open_file(mlx, path));
	return ;
}

int	set_texture_element(t_mlx *mlx, t_data *data)
{
	int			identifier;

	identifier = ft_check_identifier(mlx->data.information[0]);
	ft_check_valid_path(mlx, identifier, data->information[1]);
	if (identifier == NO && mlx->data.north == NULL)
		mlx->data.north = ft_strdup(mlx, data->information[1]);
	else if (identifier == SO && mlx->data.south == NULL)
		mlx->data.south = ft_strdup(mlx, data->information[1]);
	else if (identifier == WE && mlx->data.west == NULL)
		mlx->data.west = ft_strdup(mlx, data->information[1]);
	else if (identifier == EA && mlx->data.east == NULL)
		mlx->data.east = ft_strdup(mlx, data->information[1]);
	else if (identifier == CE && mlx->data.ceiling == NULL)
		mlx->data.ceiling = ft_strdup(mlx, data->information[1]);
	else if (identifier == FL && mlx->data.floor == NULL)
		mlx->data.floor = ft_strdup(mlx, data->information[1]);
	else
	{
		printf("identifer is duplicated\n");
		ft_free_mlx(mlx);
	}
	return (1);
}
