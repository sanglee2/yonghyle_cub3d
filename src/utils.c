/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:47:30 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 16:04:01 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 12))
		return (TRUE);
	return (FALSE);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (*(str + len))
	{
		if (ft_is_space(*(str + len)) == TRUE)
		{
			len--;
			break ;
		}
		len++;
	}
	return (len);
}
char	*ft_strdup(t_mlx *mlx, char *str)
{
	char	*tmp;
	size_t	len;
	size_t	i;

	if (*str == '\0')
		return (NULL);
	len = ft_linelen(str);
	tmp = (char *)ft_calloc(mlx, len + 1, sizeof(char));
	i = 0;
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	return (tmp);
}



int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (s1 == NULL)
		return (FALSE);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (TRUE);
	return (FALSE);
}

int	ft_is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (TRUE);
	return (FALSE);
}

char	*ft_strcpy(char *str1, char *str2)
{
	ssize_t len;
	ssize_t i;

	if (*str2 == '\0')
		return (NULL);
	len = ft_linelen(str2);
	i = 0;
	while (i < len)
	{
		str1[i] = str2[i];
		i++;
	}
	return (str1);
}