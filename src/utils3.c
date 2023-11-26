/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:47:30 by jihokim2          #+#    #+#             */
/*   Updated: 2023/11/26 16:56:54 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*ft_strcpy(char *str1, char *str2)
{
	ssize_t	len;
	ssize_t	i;

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
