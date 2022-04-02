/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:54:15 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 18:26:48 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include <math.h>

static void	orient_player(t_player *player, t_key *key)
{
	double	incr_orient;

	if (key->r_arrow)
		incr_orient = -ORIENT_STEP;
	else if (key->l_arrow)
		incr_orient = ORIENT_STEP;
	else
		return ;
	player->orientation += incr_orient;
	if (player->orientation < 0)
		player->orientation = 360 + player->orientation;
	if (player->orientation > 359)
		player->orientation = player->orientation - 360;
}

static void	update_position(double *incr_x, double *incr_y, double alpha)
{
	*incr_x += cos(degrees_to_radians(alpha)) * MOOVE_STEP;
	*incr_y += -(sin(degrees_to_radians(alpha)) * MOOVE_STEP);
}

static void	moove_player(t_player *player, t_key *key, t_map *map)
{
	double	incr_x;
	double	incr_y;

	incr_x = 0.0;
	incr_y = 0.0;
	if (key->z)
		update_position(&incr_x, &incr_y, player->orientation);
	if (key->q)
		update_position(&incr_x, &incr_y, player->orientation + 90);
	if (key->s)
		update_position(&incr_x, &incr_y, player->orientation - 180);
	if (key->d)
		update_position(&incr_x, &incr_y, player->orientation - 90);
	if (!is_in_a_wall((player->position.x + incr_x), player->position.y, map))
		player->position.x += incr_x;
	if (!is_in_a_wall(player->position.x, (player->position.y + incr_y), map))
		player->position.y += incr_y;
}

bool	update_player(t_player *player, t_key *key, t_map *map)
{
	if (!key->z && !key->q && !key->s && !key->d
		&& !key->l_arrow && !key->r_arrow)
		return (false);
	moove_player(player, key, map);
	orient_player(player, key);
	return (true);
}
