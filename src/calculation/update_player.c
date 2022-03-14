/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:54:15 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/10 21:01:38 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include <math.h>

#include <stdio.h>

static bool	is_valid_map_access(int x, int y, t_map *map)
{
	return (!(y < 0 || x < 0 || y >= map->height || x >= str_len(map->content[y])));
}

static bool	is_in_a_wall(double x, double y, t_map *map)
{
	t_position	position;

	position.x = x;
	position.y = y;
	if (!is_valid_map_access((int)x, (int)y, map))
		return (true);
	else if (does_position_touch_a_wall(position, map->content))
		return (true);
	else if (is_charset(map->content[(int)y][(int)x], "12 "))
		return (true);
	else
		return (false);
}

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
	if (is_in_a_wall((player->position.x + incr_x), (player->position.y + incr_y), map))
		return ;
	player->position.x += incr_x;
	player->position.y += incr_y;
}

bool	update_player(t_player *player, t_key *key, t_map *map) //update la struct player par rapport au keycode et return true si player change, false si non. Utiliser cette valeur de retour pour update ou non l'affichage
{
	if (!key->z && !key->q && !key->s && !key->d && !key->l_arrow && !key->r_arrow)
		return (false);
	moove_player(player, key, map);
	orient_player(player, key);
	return (true);
}
