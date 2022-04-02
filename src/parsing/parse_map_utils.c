/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:38:31 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 19:05:46 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

void	replace_connected_1_by_3(char **map, int y, int x)
{
	if (y < 0 || x < 0
		|| y >= str_tab_len(map) || x >= str_len(map[y]) || map[y][x] != '1')
		return ;
	map[y][x] = '3';
	replace_connected_1_by_3(map, y - 1, x);
	replace_connected_1_by_3(map, y + 1, x);
	replace_connected_1_by_3(map, y, x - 1);
	replace_connected_1_by_3(map, y, x + 1);
}

bool	is_in_map(t_map *map, int x, int y)
{
	return (!(y < 0 || x < 0 || y >= map->height
			|| x >= str_len(map->content[y])));
}

bool	is_zero_surrounded(t_map *map, int x, int y)
{
	int	i;
	int	j;

	j = -1;
	while (j <= 1)
	{
		i = -1;
		while (i <= 1)
		{
			if (!is_in_map(map, (x + i), (y + j))
				|| map->content[y + j][x + i] == ' ')
				return (false);
			i++;
		}
		j++;
	}
	return (true);
}
