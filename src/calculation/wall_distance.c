/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:32:54 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 18:27:14 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include <math.h>

static char	does_position_touch_a_wall_cross(t_position position, char **map)
{
	if (map[(int)position.y][(int)position.x] == '1'
		&& map[(int)position.y][(int)position.x - 1] == '1')
		return ('S');
	if (map[(int)position.y - 1][(int)position.x] == '1'
		&& map[(int)position.y - 1][(int)position.x - 1] == '1')
		return ('N');
	if (map[(int)position.y - 1][(int)position.x - 1] == '1'
		&& map[(int)position.y][(int)position.x - 1] == '1')
		return ('O');
	if (map[(int)position.y - 1][(int)position.x] == '1'
		&& map[(int)position.y][(int)position.x] == '1')
		return ('E');
	if (map[(int)position.y - 1][(int)position.x - 1] == '1')
		return ('O');
	if (map[(int)position.y - 1][(int)position.x] == '1')
		return ('N');
	if (map[(int)position.y][(int)position.x - 1] == '1')
		return ('S');
	if (map[(int)position.y][(int)position.x] == '1')
		return ('E');
	return ('\0');
}

char	does_position_touch_a_wall(t_position position, char **map)
{
	if (fmod(position.x, (double)1) > (double)0
		&& fmod(position.y, (double)1) > (double)0)
		return ('\0');
	if (fmod(position.y, (double)1) > (double)0)
	{
		if (map[(int)(position.y / (double)1)][(int)position.x] == '1')
			return ('E');
		else if (map[(int)(position.y / (double)1)][(int)position.x - 1] == '1')
			return ('O');
	}
	else if (fmod(position.x, (double)1) > (double)0)
	{
		if (map[(int)position.y][(int)position.x] == '1')
			return ('S');
		else if (map[(int)position.y - 1][(int)position.x] == '1')
			return ('N');
	}
	else
		return (does_position_touch_a_wall_cross(position, map));
	return (false);
}

t_wall	get_wall_distance(t_position player_position, double angle, char **map)
{
	t_position	current_position;
	t_wall		wall;

	current_position.x = player_position.x;
	current_position.y = player_position.y;
	while (!does_position_touch_a_wall(current_position, map))
		get_next_intersection(&current_position, angle);
	wall.distance = calc_distance(player_position, current_position);
	wall.orientation = does_position_touch_a_wall(current_position, map);
	wall.colision = current_position;
	return (wall);
}
