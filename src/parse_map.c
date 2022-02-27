/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:47:19 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/27 17:00:34 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <unistd.h>

static bool	parse_map_wrong_char(char **map)
{
	char	*line;

	if (!map)
		return (true);
	while (*map)
	{
		line = *map;
		while (*line)
		{
			if (!is_charset(*line, "012 NSOE"))
				return (true);
			line++;
		}
		map++;
	}
	return (false);
}

static int	get_n_char_in_map(char c, char **map)
{
	int		number;
	char	*line;

	number = 0;
	if (!map)
		return (0);
	while (*map)
	{
		line = *map;
		while (*line)
		{
			if (*line == c)
				number++;
			line++;
		}
		map++;
	}
	return (number);
}

static void	replace_one_by_M(char **map, int y, int x)
{
	if (y < 0 || x < 0 || y >= str_tab_len(map) || x >= str_len(map[y]) || map[y][x] != '1')
		return ;
	map[y][x] = 'M';
	replace_one_by_M(map, y - 1, x);
	replace_one_by_M(map, y + 1, x);
	replace_one_by_M(map, y, x - 1);
	replace_one_by_M(map, y, x + 1);
}

static bool	is_there_islands(char **map)
{
	int	x;

	x = 0;
	while (map[0][x] != '1')
		x++;
	replace_one_by_M(map, 0, x);
	if (get_number_of(map, '1'))
		return (true);
	else
		return (false);
}

static bool	is_in_map(char **map, int x, int y)
{
	if ()
}

static bool	is_zero_surrounded(char **map, int x, int y)

static bool	is_map_closed(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->content[y])
	{
		x = 0;
		while (map->content[y][x])
		{
			if (!is_zero_surrounded(map, x, y))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	parse_map(t_map *map, t_player *player)
{
	if (parse_map_wrong_char(map->content)
	{
		print_error("wrong char\n");
		return (true);
	}
	else if ((get_n_char_in_map('N', map->content) + get_n_char_in_map('S', map->content)
		+ get_n_char_in_map('E', map->content) +get_n_char_in_map('O', map->content)) != 1)
	{
		print_error("n_player\n");
		return (true);
	}
	if (!is_map_closed(map))
	{
		print_error("unclosed map\n");
		return (true);
	}
	//get_player(map, player);
	if (is_there_islands(map))
	{
		print_error("islands\n");
		return (true);
	}
	return (false);
}
