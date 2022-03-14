/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:32:54 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/10 20:40:54 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <math.h>

#include <stdio.h>

double	degrees_to_radians(double degrees)
{
	return (degrees * (M_PI / (double)180));
}

char	does_position_touch_a_wall(t_position position, char **map)
{
	if (fmod(position.x, (double)1) > (double)0 && fmod(position.y, (double)1) > (double)0)
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
	{
		if (map[(int)position.y][(int)position.x] == '1')
			return ('E');
		if (map[(int)position.y][(int)position.x - 1] == '1')
			return ('N');
		if (map[(int)position.y - 1][(int)position.x] == '1')
			return ('O');
		if (map[(int)position.y - 1][(int)position.x - 1] == '1')
			return ('S');
	}
	return (false);
}

static void	levelling(double *x_oppo, double *y_oppo, double x_adja, double y_adja)
{

	if (*x_oppo > y_adja)
		*x_oppo = y_adja;
	else if (*y_oppo > x_adja)
		*y_oppo = x_adja;
}
enum { TOP_RIGHT, TOP_LEFT, BOT_LEFT, BOT_RIGHT };

static void	calc_new_intersection(t_position *position, t_position plan_start, t_position plan_end, double angle)
{
	double		x_adja;
	double		y_adja;
	double		x_oppo;
	double		y_oppo;
	int			quart;

	if (angle >= (double)0 && angle <= (double)90)
		quart = TOP_RIGHT;
	else if (angle > (double)90 && angle <= (double)180)
		quart = TOP_LEFT;
	else if (angle > (double)180 && angle <= (double)270)
		quart = BOT_LEFT;
	else if (angle > (double)270 && angle < (double)360)
		quart = BOT_RIGHT;
	if (quart == TOP_RIGHT)
	{
		x_adja = position->y - plan_start.y;
		y_adja = plan_end.x - position->x;
	}
	else if (quart == TOP_LEFT)
	{
		x_adja = position->y - plan_start.y;
		y_adja = position->x - plan_start.x;
	}
	else if (quart == BOT_LEFT)
	{
		x_adja = plan_end.y - position->y;
		y_adja = position->x - plan_start.x;
	}
	else if (quart == BOT_RIGHT)
	{
		x_adja = plan_end.y - position->y;
		y_adja = plan_end.x - position->x;
	}
	if (quart == TOP_RIGHT)
	{
		x_oppo = x_adja * tan(degrees_to_radians((double)90 - angle));
		y_oppo = y_adja * tan(degrees_to_radians(angle));
	}
	else if (quart == TOP_LEFT)
	{
		x_oppo = x_adja * tan(degrees_to_radians(angle - (double)90));
		y_oppo = y_adja * tan(degrees_to_radians((double)180 - angle));
	}
	if (quart == BOT_LEFT)
	{
		x_oppo = x_adja * tan(degrees_to_radians((double)270 - angle));
		y_oppo = y_adja * tan(degrees_to_radians(angle - (double)180));
	}
	if (quart == BOT_RIGHT)
	{
		x_oppo = x_adja * tan(degrees_to_radians(angle - (double)270));
		y_oppo = y_adja * tan(degrees_to_radians((double)360 - angle));
	}
	levelling(&x_oppo, &y_oppo, x_adja, y_adja);
	if (quart == TOP_RIGHT)
	{
		position->x += x_oppo;
		position->y -= y_oppo;
	}
	else if (quart == TOP_LEFT)
	{
		position->x -= x_oppo;
		position->y -= y_oppo;
	}
	else if (quart == BOT_LEFT)
	{
		position->x -= x_oppo;
		position->y += y_oppo;
	}
	else if (quart == BOT_RIGHT)
	{
		position->x += x_oppo;
		position->y += y_oppo;
	}
}

/*
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
*/

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
	return (wall);
}
