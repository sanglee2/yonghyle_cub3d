/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:59:20 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 15:39:38 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_check_identifier(char *str)
{
	if (ft_strcmp(str, "NO") == TRUE)
		return (NO);
	else if (ft_strcmp(str, "SO") == TRUE )
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
	int i;
	i = 0;
	
	if (ft_check_identifier(data->information[0]) == -1 || \
							data->information[1] == NULL || \
							data->information[2] != NULL)
	{
		while(data->information[i])
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
	int fd;
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
		printf("identifer is duplicated\n");			// free하고 에러 처리하는 함수.
		ft_free_mlx(mlx);
	}
	return (1);
}

void	ft_get_texture(t_mlx *mlx)
{
	if (mlx->data.information[0] == NULL)
		return ;
	ft_check_texture_element(mlx, &mlx->data);
	set_texture_element(mlx, &mlx->data);
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
			{
				printf("ft_syntax_of_serial_comma\n");
				ft_free_mlx(mlx);
			}
			serial_comma++;
			comma++;
			num_flag = 0;
		}
		else
		{
			printf("ft_syntax_of_white_space");
			ft_free_mlx(mlx);
		}
		str++;
	}
	if (element > 3 || comma != 2)
	{
		printf("ft_check_element_comma\n");	
		ft_free_mlx(mlx);
	}
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
		if (mlx->data.line == NULL)	// 1줄씩 읽어오기 - 반복문(탈출조건). line = NULL이면 탈출.
			break ;
		mlx->data.information = ft_split(mlx->data.line);
		ft_get_texture(mlx);		// 각 line에서 map대한 유효한 정보 - 동서남북 천장/바닥.
		ft_free_info(&mlx->data); // information 구조체 free.
		ft_free_line(mlx);			// data.line을 free하고, Null pointer 초기화. - gnl 내에서 malloc
		mlx->data.line = NULL;
		if (mlx->data.north && mlx->data.south && mlx->data.west && \
			mlx->data.east && mlx->data.floor && mlx->data.ceiling)	// 방향정보, 위아래 정보 전부 획들 했을 경우 - 나가기, 위에서 정보들 다 채울 수 밖에 없음.
			break ;
	}
	mlx->data.intfloor = ft_edit_color(mlx, mlx->data.floor); 		// RGB 값으로 바꾸자!
	mlx->data.intceiling = ft_edit_color(mlx, mlx->data.ceiling);	// RGB 값으로 바꾸자!
}
