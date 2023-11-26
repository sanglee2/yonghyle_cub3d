/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:57:51 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 15:52:56 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_syntax_of_map(t_mlx *mlx, char *line)
{
	while (*line)
	{
		if (!(ft_is_space(*line) == TRUE || *line == '1' || *line == '0' || \
			*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E'))
		{
			printf("ft_syntax_of_map\n");
			ft_free_mlx(mlx);
		}
		if (*line == '\n')
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
			temp[height] = mlx->map[height];
		free(mlx->map);
		temp[height] = ft_linecpy(mlx, mlx->data.line);
		temp[height + 1] = NULL;
		mlx->map = temp;
	}
}

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
	return (TRUE);
}

void	ft_get_map(t_mlx *mlx)
{
	int		already_map;

	already_map = FALSE;
	while (TRUE)
	{
		mlx->data.line = get_next_line(mlx->data.fd);
		if (mlx->data.line == NULL)
			break;
		if (ft_is_empty_line(mlx->data.line) == TRUE)
		{
			ft_free_line(mlx);
			if (mlx->map)
				already_map = TRUE;			
			continue;
		}
		if (mlx->data.line && already_map == TRUE)
		{
			printf("ft_get_map\n");
			ft_free_mlx(mlx);
		}
		ft_syntax_of_map(mlx, mlx->data.line);
		ft_line_to_map(mlx);
		ft_free_line(mlx);
	}
}
