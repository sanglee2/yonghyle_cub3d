/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.d                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanglee2 <sanglee2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:02:31 by sanglee2          #+#    #+#             */
/*   Updated: 2023/11/26 10:03:14 by sanglee2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




void	check_map_is_closed(char **map, t_map *map_info)
{
	int	column;
	int	row;

	column = 0;
	while (column < map_info->height)
	{
		row = 0;
		while (row < map_info->width)
		{
			if (map[column][row] == '0' || map[column][row] == 'N' || \
				map[column][row] == 'S' || map[column][row] == 'E' || \
				map[column][row] == 'W')
				check_is_surrouned(map, column, row, map_info);
			++row;
		}
		++column;
	}
}

void	check_north_is_empty(t_map *map_info, char **map, int h, int w)
{
	if (h - 1 < 0)
		ctrl_error("map must be closed by wall\n");
	else if (h - 1 >= 0 && (is_empty_space(map[h - 1][w]) == FALSE && map[h - 1][w] != '1'))
		ctrl_error("map must be closed by wall\n");
	return ;
}

void	check_south_is_empty(t_map *map_info, char **map, int h, int w)
{
	if (h + 1 >= map_info->height)
		ctrl_error("map must be closed by wall\n");
	else if (is_empty_space(map[h + 1][w]) == FALSE && map[h + 1][w] != '1')
		ctrl_error("map must be closed by wall\n");
	return ;
}

void	check_east_is_empty(t_map *map_info, char **map, int h, int w)
{
	if (w + 1 >= map_info->width)
		ctrl_error("map must be closed by wall\n");
	else if (is_empty_space(map[h][w + 1]) == FALSE && map[h][w + 1] != '1')
		ctrl_error("map must be closed by wall\n");
	return ;
}

void	check_west_is_empty(t_map *map_info, char **map, int h, int w)
{
	if (w - 1 < 0)
		ctrl_error("map must be closed by wall\n");
	else if (is_empty_space(map[h][w - 1]) == FALSE && map[h][w - 1] != '1')
		ctrl_error("map must be closed by wall\n");
	return ;
}

void	check_is_surrouned(char **map, int h, int w, t_map *map_info)
{
	check_north_is_empty(map_info, map, h, w);
	check_south_is_empty(map_info, map, h, w);
	check_east_is_empty(map_info, map, h, w);
	check_west_is_empty(map_info, map, h, w);
}