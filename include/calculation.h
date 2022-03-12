/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:42:44 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/10 17:17:12 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALCULATION_H
# define CALCULATION_H

# include "header.h"

# define KEY_RIGHT_ARROW 65363
# define KEY_LEFT_ARROW 65361
# define ORIENT_STEP 1
# define MOOVE_STEP 0.2

typedef struct s_column_info
{
	int	start;
	int	end;
}	t_column_info;

bool	update_player(t_player *player, int keycode, t_map *map);
bool	does_position_touch_a_wall(t_position position, char **map);

#endif
