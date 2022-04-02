/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:53:48 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 16:53:51 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <math.h>

double	degrees_to_radians(double degrees)
{
	return (degrees * (M_PI / (double)180));
}

double	calc_distance(t_position position_1, t_position position_2)
{
	return (sqrt(pow((position_1.x - position_2.x), 2)
			+ pow((position_1.y - position_2.y), 2)));
}
