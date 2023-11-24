/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:59:20 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/24 14:38:03 by sanglee2         ###   ########.fr       */
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
	else if (*(line + 3) && ft_strcmp(line, "NO ") == TRUE)			
		mlx->data.north = ft_str_to_mlx(mlx, line + 3); 			
	else if (*(line + 3) && ft_strcmp(line, "SO ") == TRUE)
		mlx->data.south = ft_str_to_mlx(mlx, line + 3);
	else if (*(line + 3) && ft_strcmp(line, "WE ") == TRUE)
		mlx->data.west = ft_str_to_mlx(mlx, line + 3);
	else if (*(line + 3) && ft_strcmp(line, "EA ") == TRUE)
		mlx->data.east = ft_str_to_mlx(mlx, line + 3);
	else if (*(line + 2) && ft_strcmp(line, "F ") == TRUE)
		mlx->data.floor = ft_str_to_mlx(mlx, line + 2);
	else if (*(line + 2) && ft_strcmp(line, "C ") == TRUE)
		mlx->data.ceiling = ft_str_to_mlx(mlx, line + 2);
}

void	ft_syntax_of_color(t_mlx *mlx, char *str)		
{
	int comma;
	int element;
	int	num_flag;
	int serial_comma;

	comma = 0;
	element = 0;
	num_flag = 0;
	serial_comma = 0;

	while (*str != '\0')						
	{
		if (ft_is_num(*str) == TRUE)
		{
			if (num_flag == 0)
			{
				element++;
				num_flag = 1;
			}
			serial_comma = 0;
		}
		else if (*str == ',' && serial_comma == 0)
		{
			if (comma == 2)
				ft_free_mlx(mlx);
			serial_comma++;
			comma++;
			num_flag = 0;
		}
		else
		{
			ft_free_mlx(mlx);
		}
		str++;
	}
	if (element > 3 || comma != 2)	
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
	if (mlx->data.R > 255 || mlx->data.G > 255 || mlx->data.B > 255) 	
		ft_free_mlx(mlx);
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
		if (mlx->data.line == NULL)						// 1줄씩 읽어오기 - 반복문(탈출조건)
			break ;
		ft_get_texture(mlx, mlx->data.line);			// 각 line에서 map대한 유효한 정보 - 동서남북 천장/바닥.
		ft_free_line(mlx);								// data.line을 free하고, Null pointer 초기화. - gnl 내에서 malloc
		mlx->data.line = NULL;
		if (mlx->data.north && mlx->data.south && mlx->data.west && \
			mlx->data.east && mlx->data.floor && mlx->data.ceiling)	// 방향정보, 위아래 정보 전부 획들 했을 경우 - 나가기, 위에서 정보들 다 채울 수 밖에 없음.
			break ;
	}
		
	mlx->data.intfloor = ft_edit_color(mlx, mlx->data.floor); 		// RGB 값으로 바꾸자!
	mlx->data.intceiling = ft_edit_color(mlx, mlx->data.ceiling);	// RGB 값으로 바꾸자!
}
