/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:57:51 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/19 19:59:05 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_syntax_of_map(t_mlx *mlx, char *line)
{
	while (*line)
	{
		if (!(ft_is_space(*line) == TRUE || *line == '1' || *line == '0' || \
			*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E'))
			ft_free_mlx(mlx);
		if (*line == '\n')		// Q.개행일 때, 0처리 왜 한 거지?
			*line = 0;
		line++;
	}
}

void	ft_line_to_map(t_mlx *mlx)
{
	char	**temp;
	int		height;

	if (mlx->map == NULL)
	{
		mlx->map = (char **)ft_calloc(mlx, 2, sizeof(char *));
		mlx->map[0] = ft_linecpy(mlx, mlx->data.line);
		mlx->map[1] = NULL;
	}
	else
	{
		height = ft_arrlen(mlx->map);
		temp = (char **)ft_calloc(mlx, height + 2, sizeof(char *));
		height = -1;
		while (mlx->map[++height])
			temp[height] = mlx->map[height];				// arrlen으로 구한 0부터 height -1까지.
		free(mlx->map);
		temp[height] = ft_linecpy(mlx, mlx->data.line);
		temp[height + 1] = NULL;
		mlx->map = temp;
		// printf("map 1 line: %s\n", mlx->map[height]);
	}
}

// add_line_to_arr 예전 함수 - ft_line_to_map과 상동.

// void	ft_add_line_to_arr(t_mlx *mlx) // 1줄 -> 이차원 배열인 map에 요소로 저장.
// {
// 	char	**tmp;
// 	int		i;

// 	if (mlx->map == NULL)
// 	{
// 		mlx->map = (char **)ft_calloc(mlx, 2, sizeof(char *));
// 		mlx->map[0] = ft_linecpy(mlx, mlx->data.line);
// 		mlx->map[1] = NULL;
// 	}
// 	else
// 	{
// 		i = ft_arrlen(mlx->map);
// 		tmp = (char **)ft_calloc(mlx, i + 2, sizeof(char *)); 
// 		i = -1;
// 		while (mlx->map[++i]) 
// 			tmp[i] = mlx->map[i];
// 		tmp[i] = ft_linecpy(mlx, mlx->data.line); 
// 		free(mlx->map);
// 		mlx->map = tmp;
// 	}
// }

int	ft_is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_is_space(line[i]) == TRUE)
			i++;
		else
			return (FALSE);
	}
	return (TRUE);										// 개행인 것도 TRUE를 반환하게 됨.
}

void	ft_get_map(t_mlx *mlx)							// 조금 더 깔끔히 바꿀 순 없을까?!
{
	int		already_map;
	// char	*line;

	already_map = FALSE;

	while (TRUE)										// 1번에 읽어오는게 더 편하니까 -- 일단 에러처리 하는 것으로 가자.
	{
		mlx->data.line = get_next_line(mlx->data.fd);  // 탈출하는 거 없어 보이는데 괜찮나 - 괜찮다.
		if (mlx->data.line == NULL)
			break;
		if (ft_is_empty_line(mlx->data.line) == TRUE)			// 이걸 함수로 깔끔하게 만들 순 없을까?
		{
			ft_free_line(mlx);
			if (mlx->map)
				already_map = TRUE;			
			continue;
		}
		if (mlx->data.line && already_map == TRUE)
			ft_free_mlx(mlx);						// 이 분기에서 빠져버리게 - 에러 문구 처리도 같이.
		ft_syntax_of_map(mlx, mlx->data.line);
		ft_line_to_map(mlx);						// 맵 옮기는 작업 잘할 것.
		ft_free_line(mlx);
	}
	// int i;
	// i = 0;
	// while(mlx->map[i])
	// {
	// 	printf("mapmapmap:%s\n", mlx->map[i]);
	// 	i++;
	// }
}




// get_map 원본.

// void	ft_get_map(t_mlx *mlx)
// {
// 	int map_done;

// 	map_done = 0;
// 	while (1)
// 	{
// 		mlx->data.line = get_next_line(mlx->data.fd);
// 		if (mlx->data.line == NULL || mlx->data.line[0] == '\0') // 맵이 없이 끝나는 경우도 예외처리.
// 			break ;
// 		if (ft_is_empty_line(mlx->data.line) == TRUE)			// 중간에 개행만 있거나, white_space로만 차있다면 처리.
// 		{
// 			ft_free_line(mlx);									// 해당 line만 free.
// 			if (mlx->map && map_done == 0)
// 				map_done = 1;					
// 			continue ;											// 밑의 구문 내려가지 않고, 다시 한 번 읽어오게끔.
// 		}
// 		if (mlx->map && map_done)								// 중간에 개행이 있는 지도 -> 성부 다 에러처리 한 것인가?!
// 			ft_free_mlx(mlx);
// 		ft_syntax_of_map(mlx, mlx->data.line);
// 		ft_add_line_to_arr(mlx);								// 1줄씩 -> map 2차원 배열에 담기. map 완성
// 		ft_free_line(mlx);										// line 다 쓰고 해제.
// 	}
// }
