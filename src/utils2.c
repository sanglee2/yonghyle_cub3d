/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihokim2 <jihokim2@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:45:06 by jihokim2          #+#    #+#             */
/*   Updated: 2023/10/28 12:47:18 by jihokim2         ###   ########.fr       */
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
	int		i;

	tmp = (char *)ft_calloc(mlx, ft_linelen(line) + 1, sizeof(char));
	i = -1;
	while (line[++i])
		tmp[i] = line[i];
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
	while (--size > 0)
		ptr[size] = 0;
	ptr[size] = 0;
}

void	*ft_calloc(t_mlx *mlx, size_t count, size_t size)
{
	void	*arr;

	arr = (void *)malloc(count * size);
	if (!arr)
		ft_free_mlx(mlx);
	ft_bzero(arr, (count * size));
	return (arr);
}
