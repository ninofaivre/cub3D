/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:32:54 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/07 22:08:28 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <math.h>

#include <stdio.h>

static double	degrees_to_radians(double degrees)
{
	return (degrees * (M_PI / (double)180));
}

static bool	does_position_touch_a_wall(t_position position, char **map)
{
	if (fmod(position.x, (double)1) > (double)0 && fmod(position.y, (double)1) > (double)0)
		return (false);
	if (fmod(position.y, (double)1) > (double)0)
	{
		if (map[(int)(position.y / (double)1)][(int)position.x] == '1'
			|| map[(int)(position.y / (double)1)][(int)position.x - 1] == '1')
			return (true);
	}
	else if (fmod(position.x, (double)1) > (double)0)
	{
		if (map[(int)position.y][(int)(position.x / (double)1)] == '1'
			|| map[(int)position.y - 1][(int)(position.x / (double)1)] == '1')
			return (true);
	}
	else
	{
		if (map[(int)position.y][(int)position.x] == '1'
			|| map[(int)position.y][(int)position.x - 1] == '1'
			|| map[(int)position.y - 1][(int)position.x] == '1'
			|| map[(int)position.y - 1][(int)position.x - 1] == '1')
			return (true);
	}
	return (false);
}

static void	levelling(t_position *position, t_position plan_start, t_position plan_end)
{
	if (position->x < plan_start.x)
		position->x = plan_start.x;
	else if (position->x > plan_end.x)
		position->x = plan_end.x;
	if (position->y < plan_start.y)
		position->y = plan_start.y;
	else if (position->y > plan_end.y)
		position->y = plan_end.y;
}

static void	calc_new_intersection(t_position *position, t_position plan_start, t_position plan_end, double angle)
{
	t_position	new_position;
	
	if (angle >= (double)0 && angle <= (double)90)
	{
		new_position.x = position->x + ((position->y - plan_start.y) * tan(degrees_to_radians((double)90 - angle)));
		new_position.y = position->y - ((plan_end.x - position->x) * tan(degrees_to_radians(angle)));
	}
	else if (angle > (double)90 && angle <= (double)180)
	{
		new_position.x = position->x - ((position->y - plan_start.y) * tan(degrees_to_radians(angle - (double)90)));
		new_position.y = position->y - ((position->x - plan_start.x) * tan(degrees_to_radians((double)180 - angle)));
	}
	else if (angle > (double)180 && angle <= (double)270)
	{
		new_position.x = position->x - ((position->y - plan_end.y) * tan(degrees_to_radians((double)270 - angle)));
		new_position.y = position->y + ((position->x - plan_start.x) * tan(degrees_to_radians(angle - (double)180)));
	}
	else if (angle > (double)270 && angle < (double)360)
	{
		new_position.x = position->x + ((position->y - plan_end.y) * tan(degrees_to_radians(angle - (double)270)));
		new_position.y = position->y + ((plan_end.x - position->x) * tan(degrees_to_radians((double) 360 - angle)));
	}
	else
		return ;
	levelling(&new_position, plan_start, plan_end);
	position->x = new_position.x;
	position->y = new_position.y;
}

static void	get_next_intersection(t_position *position, double angle)
{
	t_position	plan_start;
	t_position	plan_end;

	if (fmod(position->x, (double)1) > (double)0 && fmod(position->y, (double)1) > (double)0)
	{
		plan_start.x = position->x - fmod(position->x, (double)1);
		plan_end.x = plan_start.x + (double)1;
		plan_start.y = position->y - fmod(position->y, (double)1);
		plan_end.y = plan_start.y + (double)1;
	}
	else if (fmod(position->y, (double)1) > (double)0)
	{
		plan_start.x = position->x - (double)1;
		plan_end.x = position->x + (double)1;
		plan_start.y = position->y - fmod(position->y, (double)1);
		plan_end.y = plan_start.y + (double)1;
	}
	else if (fmod(position->x, (double)1) > (double)0)
	{
		plan_start.x = position->x - fmod(position->x, (double)1);
		plan_end.x = plan_start.x + (double)1;
		plan_start.y = position->y - (double)1;
		plan_end.y = position->y + (double)1;
	}
	else
	{
		plan_start.x = position->x - (double)1;
		plan_end.x = position->x + (double)1;
		plan_start.y = position->y - (double)1;
		plan_end.y = position->y + (double)1;
	}
	calc_new_intersection(position, plan_start, plan_end, angle);
}

static double	calc_distance(t_position position_1, t_position position_2)
{
	return (sqrt(pow((position_1.x - position_2.x), 2) + pow((position_1.y - position_2.y), 2)));
}

double	get_wall_distance(t_position player_position, double angle, char **map)
{
	t_position	current_position;

	current_position.x = player_position.x;
	current_position.y = player_position.y;
	
	while (!does_position_touch_a_wall(current_position, map))
		get_next_intersection(&current_position, angle);
	return (calc_distance(player_position, current_position));
}
