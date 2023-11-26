/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:44:44 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/26 17:58:16 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	while (i < n && s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

void	ft_word_count(char *str, int *i, int *word_count)
{
	*word_count = 0;
	while (str[*i])
	{
		while (str[*i] && is_space(str[*i]))
			(*i)++;
		if (str[*i])
			(*word_count)++;
		while (str[*i] && !is_space(str[*i]))
			(*i)++;
	}
}

char	**ft_split(char *str, int i, int j, int k)
{
	int		word_count;
	char	**ret;

	ft_word_count(str, &i, &word_count);
	ret = (char **)malloc(sizeof(char *) * (word_count + 1));
	i = 0;
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		j = i;
		while (str[i] && !is_space(str[i]))
			i++;
		if (i > j)
		{
			ret[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			ft_strncpy(ret[k], &str[j], i - j);
			k++;
		}
	}
	ret[k] = NULL;
	return (ret);
}
