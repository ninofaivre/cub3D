/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:47:19 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/28 14:38:24 by nfaivre          ###   ########.fr       */
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

static int	get_n_char_in_str_tab(char c, char **str_tab)
{
	int		number;
	char	*str;

	number = 0;
	if (!str_tab)
		return (0);
	while (*str_tab)
	{
		str = *str_tab;
		while (*str)
		{
			if (*str == c)
				number++;
			str++;
		}
		str_tab++;
	}
	return (number);
}

static void	replace_all_charset_by_char_in_str_tab(char *charset, char replace, char **str_tab)
{
	char	*str;
	if (!str_tab)
		return ;
	while (*str_tab)
	{
		str = *str_tab;
		while (*str)
		{
			if (is_charset(*str, charset))
				*str = replace;
			str++;
		}
		str_tab++;
	}
}

static void	replace_connected_1_by_M(char **map, int y, int x)
{
	if (y < 0 || x < 0
		|| y >= str_tab_len(map) || x >= str_len(map[y]) || map[y][x] != '1')
		return ;
	map[y][x] = 'M';
	replace_connected_1_by_M(map, y - 1, x);
	replace_connected_1_by_M(map, y + 1, x);
	replace_connected_1_by_M(map, y, x - 1);
	replace_connected_1_by_M(map, y, x + 1);
}

static bool	is_there_islands(char **map)
{
	char	**cpy_map;
	int	x;

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
	replace_connected_1_by_M(cpy_map, 0, x);
	if (get_n_char_in_str_tab('1', cpy_map))
	{
		free_str_tab(&cpy_map);
		print_error("islands\n");
		return (true);
	}
	free_str_tab(&cpy_map);
	return (false);
}

static bool	is_in_map(t_map *map, int x, int y)
{
	return (!(y < 0 || x < 0 || y >= map->height
		|| x >= str_len(map->content[y])));
}

static bool	is_zero_surrounded(t_map *map, int x, int y)
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
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

static void	fill_player(t_player *player, char **map)
{
	float	x;
	float	y;

	y = 0;
	(void)player;
	while (map[(int)y])
	{
		x = 0;
		while (!is_charset(map[(int)y][(int)x], "NSEW") && map[(int)y][(int)x])
			x++;
		if (map[(int)y][(int)x])
			break ;
		y++;
	}
	player->position.x = x;
	player->position.y = y;
	player->orientation = (float)(90 *(((map[(int)y][(int)x] == 'E') * 0)
							+ ((map[(int)y][(int)x] == 'S') * 1)
							+ ((map[(int)y][(int)x] == 'W') * 2)
							+ ((map[(int)y][(int)x] == 'N') * 3)));
}

bool	parse_map(t_map *map, t_player *player)
{
	if (parse_map_wrong_char(map->content))
	{
		print_error("wrong char\n");
		return (true);
	}
	else if ((get_n_char_in_str_tab('N', map->content) + get_n_char_in_str_tab('S', map->content)
		+ get_n_char_in_str_tab('E', map->content) +get_n_char_in_str_tab('O', map->content)) != 1)
	{
		print_error("n_player\n");
		return (true); 
	}
	fill_player(player, map->content);
	replace_all_charset_by_char_in_str_tab("NSEW", '0', map->content);
	if (!is_map_closed(map))
	{
		print_error("unclosed map\n");
		return (true);
	}
	if (is_there_islands(map->content))
		return (true);
	return (false);
}
