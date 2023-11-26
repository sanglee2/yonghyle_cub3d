/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:45:06 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 16:04:19 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_linelen(char *line)
{
	int	len;

	len = 0;
	while (line[len])
		len++;
	return (len);
}

char	*ft_linecpy(t_mlx *mlx, char *line)
{
	char	*tmp;
	int		len;
	int		i;

	len = ft_linelen(line);
	tmp = (char *)ft_calloc(mlx, len + 1, sizeof(char));
	i = 0;
	while (i < len)
	{
		tmp[i] = line[i];
		i++;
	}
	return (tmp);
}

int	ft_arrlen(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

void	ft_bzero(void *str, size_t size)
{
	unsigned char	*ptr;

	if (!size)
		return ;
	ptr = (unsigned char *)str;
	while(--size > 0)
		ptr[size] = 0;
	ptr[size] = 0;	
}

void	*ft_calloc(t_mlx *mlx, size_t count, size_t size)
{ 	
	(void)	mlx;
	void	*arr;

	arr = (void *)malloc(count * size);
	if (!arr)
	{
		printf("ft_calloc\n");	
		ft_free_mlx(mlx);
	}
	ft_bzero(arr, (count * size));
	return (arr);
}
