/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:47:19 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/26 20:53:28 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <unistd.h>

enum {RIGHT, LEFT, BOT, TOP};

static bool	parse_one_line_wrong_char(char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (!is_charset(*line, "012 NSOE"))
			return (true);
		line++;
	}
	return (false);
}

static bool	parse_map_wrong_char(char **map)
{
	if (!map)
		return (true);
	while (*map)
	{
		if (parse_one_line_wrong_char(*map))
			return (true);
		map++;
	}
	return (false);
}

static bool	valid_pos(int y, int x, char **map)
{
	return (!(y < 0 || x < 0 || !map[y] || !map[y][x]));
}

static void	go_right_bottom(char **map, t_position *pos)
{
	int	last_dir;

	last_dir = RIGHT; 
	while (map[pos->y])
	{
		printf("x : %i, y : %i\n", pos->x, pos->y);
		if (valid_pos(pos->y, (pos->x + 1), map) && map[pos->y][pos->x + 1] == '1' && last_dir != LEFT)
		{
			pos->x++;
			last_dir = RIGHT;
		}
		else if (valid_pos((pos->y + 1), pos->x, map) && map[pos->y + 1][pos->x] == '1' && last_dir != TOP)
		{
			pos->y++;
			last_dir = BOT;
		}
		else if (valid_pos((pos->y), (pos->x - 1), map) && map[pos->y][pos->x - 1] == '1')
		{
			pos->x--;
			last_dir = LEFT;
		}
		else if (valid_pos((pos->y - 1), pos->x, map) && map[pos->y - 1][pos->x] == '1')
		{
			pos->y--;
			last_dir = TOP;
		}
	}
}

static bool	is_map_closed(char **map)
{
	t_position	position;

	position.y = 0;
	position.x = 0;
	while (map[0][position.x] != '1' && map[0][position.x])
		position.x++;
	go_right_bottom(map, &position);
	return (true);
}

bool	parse_map(char **map)
{
	if (parse_map_wrong_char(map) || !is_map_closed(map))
		return (true);
	return (false);
}
