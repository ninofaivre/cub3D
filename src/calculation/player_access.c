/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_access.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:54:15 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 18:13:27 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include "utils.h"
#include <math.h>

static bool	is_valid_map_access(int x, int y, t_map *map)
{
	return (!(y < 0 || x < 0 || y >= map->height
			|| x >= str_len(map->content[y])));
}

bool	is_in_a_wall(double x, double y, t_map *map)
{
	t_position	position;

	position.x = x;
	position.y = y;
	if (!is_valid_map_access((int)x, (int)y, map))
		return (true);
	else if (does_position_touch_a_wall(position, map->content))
		return (true);
	else if (is_charset(map->content[(int)y][(int)x], "1 "))
		return (true);
	else
		return (false);
}
