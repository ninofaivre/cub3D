/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:54:11 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 18:04:39 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include <math.h>

static void	levelling(t_side_lenght *side_lenght)
{
	if (side_lenght->x_oppo > side_lenght->y_adja)
		side_lenght->x_oppo = side_lenght->y_adja;
	else if (side_lenght->y_oppo > side_lenght->x_adja)
		side_lenght->y_oppo = side_lenght->x_adja;
}

static void	calc_oppo(t_side_lenght *sl, double angle)
{
	if (angle >= (double)0 && angle <= (double)90)
	{
		sl->x_oppo = sl->x_adja * tan(degrees_to_radians((double)90 - angle));
		sl->y_oppo = sl->y_adja * tan(degrees_to_radians(angle));
	}
	else if (angle > (double)90 && angle <= (double)180)
	{
		sl->x_oppo = sl->x_adja * tan(degrees_to_radians(angle - (double)90));
		sl->y_oppo = sl->y_adja * tan(degrees_to_radians((double)180 - angle));
	}
	else if (angle > (double)180 && angle <= (double)270)
	{
		sl->x_oppo = sl->x_adja * tan(degrees_to_radians((double)270 - angle));
		sl->y_oppo = sl->y_adja * tan(degrees_to_radians(angle - (double)180));
	}
	else if (angle > (double)270 && angle < (double)360)
	{
		sl->x_oppo = sl->x_adja * tan(degrees_to_radians(angle - (double)270));
		sl->y_oppo = sl->y_adja * tan(degrees_to_radians((double)360 - angle));
	}
}

static void	calc_new_intersection(t_position *position, t_position plan_start,
t_position plan_end, double angle)
{
	t_side_lenght	side_lenght;

	side_lenght.x_adja = (double)0.0;
	side_lenght.y_adja = (double)0.0;
	side_lenght.x_oppo = (double)0.0;
	side_lenght.y_oppo = (double)0.0;
	if (angle >= (double)0 && angle <= (double)180)
		side_lenght.x_adja = position->y - plan_start.y;
	else if (angle > (double)180 && angle < (double)360)
		side_lenght.x_adja = plan_end.y - position->y;
	if (angle > (double)90 && angle <= (double)270)
		side_lenght.y_adja = position->x - plan_start.x;
	else if (angle > (double)270 || angle <= 90)
		side_lenght.y_adja = plan_end.x - position->x;
	calc_oppo(&side_lenght, angle);
	levelling(&side_lenght);
	if (angle > (double)270 || angle <= 90)
		position->x += side_lenght.x_oppo;
	else if (angle > (double)90 && angle <= (double)270)
		position->x -= side_lenght.x_oppo;
	if (angle >= (double)0 && angle <= (double)180)
		position->y -= side_lenght.y_oppo;
	else if (angle > (double)180 && angle < (double)360)
		position->y += side_lenght.y_oppo;
}

void	get_next_intersection(t_position *position, double angle)
{
	t_position	plan_start;
	t_position	plan_end;

	if (fmod(position->x, (double)1) > (double)0)
	{
		plan_start.x = position->x - fmod(position->x, (double)1);
		plan_end.x = plan_start.x + (double)1;
	}
	else
	{
		plan_start.x = position->x - (double)1;
		plan_end.x = position->x + (double)1;
	}
	if (fmod(position->y, (double)1) > (double)0)
	{
		plan_start.y = position->y - fmod(position->y, (double)1);
		plan_end.y = plan_start.y + (double)1;
	}
	else
	{
		plan_start.y = position->y - (double)1;
		plan_end.y = position->y + (double)1;
	}
	calc_new_intersection(position, plan_start, plan_end, angle);
}
