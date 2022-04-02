/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:47:19 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 19:04:14 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

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
			{
				print_error("wrong char\n");
				return (true);
			}
			line++;
		}
		map++;
	}
	return (false);
}

static bool	is_there_islands(char **map)
{
	char	**cpy_map;
	int		x;

	cpy_map = str_tab_dupe(map);
	if (!cpy_map)
	{
		print_error("Malloc\n");
		return (true);
	}
	replace_all_charset_by_char_in_str_tab("0", '1', cpy_map);
	x = 0;
	while (map[0][x] != '1')
		x++;
	replace_connected_1_by_3(cpy_map, 0, x);
	if (get_n_char_in_str_tab('1', cpy_map))
	{
		free_str_tab(&cpy_map);
		print_error("islands\n");
		return (true);
	}
	free_str_tab(&cpy_map);
	return (false);
}

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
			if (map->content[y][x] == '0'
				&& !is_zero_surrounded(map, x, y))
			{
				print_error("unclosed map\n");
				return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

static void	fill_player(t_player *player, char **map)
{
	double	x;
	double	y;

	y = 0;
	while (map[(int)y])
	{
		x = 0;
		while (!is_charset(map[(int)y][(int)x], "NSEW") && map[(int)y][(int)x])
			x++;
		if (map[(int)y][(int)x])
			break ;
		y++;
	}
	player->position.x = x + (double)0.5;
	player->position.y = y + (double)0.5;
	player->orientation = (double)(90 *(((map[(int)y][(int)x] == 'E') * 0)
				+ ((map[(int)y][(int)x] == 'N') * 1)
				+ ((map[(int)y][(int)x] == 'W') * 2)
				+ ((map[(int)y][(int)x] == 'S') * 3)));
}

bool	parse_map(t_map *map, t_player *player)
{
	if (does_str_tab_contains_empty_str(map->content))
	{
		print_error("empty line in map\n");
		return (true);
	}
	else if (parse_map_wrong_char(map->content))
		return (true);
	else if ((get_n_char_in_str_tab('N', map->content)
			+ get_n_char_in_str_tab('S', map->content)
			+ get_n_char_in_str_tab('E', map->content)
			+ get_n_char_in_str_tab('O', map->content)) != 1)
	{
		print_error("n_player\n");
		return (true);
	}
	fill_player(player, map->content);
	replace_all_charset_by_char_in_str_tab("NSEW", '0', map->content);
	if (!is_map_closed(map) || is_there_islands(map->content))
		return (true);
	return (false);
}
