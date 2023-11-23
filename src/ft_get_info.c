/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:59:20 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/20 02:14:39 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	ft_file_check(t_mlx *mlx, char *line)
// {
		// texture에 쓴 파일명이 안 열리는 경우, error 처리를 해야 함.


// }


void	ft_get_texture(t_mlx *mlx, char *line)
{
	// printf("line : %s\n", line); 			
	if (*line == '\0' || *line == '\n')			// 값x, 개행 존재하는 경우.
		return ;
	while (ft_is_space(*line) == TRUE)			// 구성요소 서두에 공백은 지나간다.	// 공백까진 밀어주는 작업을 한다.
		line++;
	if (*line == '\0')							// 공백으로만 끝나는 1줄, 바로 다음 줄로 넘어 갈 수 있도록. 넘겨주기.	
		return ;
	else if (*(line + 3) && ft_strcmp(line, "NO ") == TRUE)			// line에서 기준 문자 먼저 비교
		mlx->data.north = ft_str_to_mlx(mlx, line + 3); 			// 시작점 기준 - 그 문자 뒤에 것.
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
	// printf("mlx->data :%s\n", mlx->data.north);					// 왜 여기서는 개행이 두 개씩 낄까?! // 전부 다 개행, 개행 껴서 갖고, 갖고온다.
}

// void	ft_syntax_of_color(t_mlx *mlx, char *str)
// {
// 	int	num;
// 	int	comma;

// 	num = 0;
// 	comma = 0;
// 	while (*str)
// 	{
// 		if (*str == ',')
// 		{
// 			if (comma == 2 || num <= 0 || num >= 4)	// 잘못된 에러인 경우
// 				ft_free_mlx(mlx);					// error 문구를 띄워주고 해결을 함.
// 			comma++;
// 			num = 0;
// 		}
// 		else if (ft_is_num(*str) == TRUE)			// 자릿수  4개
// 			num++;
// 		else
// 			ft_free_mlx(mlx);
// 		str++;
// 	}
// 	if (num <= 0 || num >= 4 || comma != 2)
// 		ft_free_mlx(mlx);
// }

void	ft_syntax_of_color(t_mlx *mlx, char *str)		// str에 대해서 다른 구조체로 테스트 해보기.
{
	int comma;
	int element;
	int	num_flag;
	int serial_comma;

	comma = 0;
	element = 0;
	num_flag = 0;
	serial_comma = 0;

	// printf("str:%s\n", str);

	while (*str != '\0')						// 앞부분의 공백은 어떻게 할 거냐
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
			// printf("여기 : %c\n", *str);
			ft_free_mlx(mlx);
			// printf("hereeeee!\n");
		}
		// printf("repeat\n");
		str++;
	}
	if (element > 3 || comma != 2)	// 콤마 기준 숫자 3개.
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
	if (mlx->data.R > 255 || mlx->data.G > 255 || mlx->data.B > 255) 	// RGB 값 넘는경우 처리.
		ft_free_mlx(mlx);
}

int	ft_edit_color(t_mlx *mlx, char *str)
{
	if (str == NULL)				// str == NULL -> 실패한 경우니까 바로해제
		ft_free_mlx(mlx);			// map, tmp, line 전부 해제.
	ft_syntax_of_color(mlx, str);	// 255,255,255 쪽 구성요소 체크.
	ft_str_to_int(mlx, str);		// atoi 사용여부.
	return ((mlx->data.R << 16) | (mlx->data.G << 8) | mlx->data.B); // or로 비트연산
}

void	ft_get_info(t_mlx *mlx)							// 정보들 가져오는 작업만 해주는 함수.						
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
