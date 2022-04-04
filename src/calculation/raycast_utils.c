/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/04 21:50:30 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"

void	cpy_data_pixel(char *ptr_pix_data1, char *ptr_pix_data2,
bool same_endian)
{
	if (same_endian)
	{
		ptr_pix_data1[0] = ptr_pix_data2[0];
		ptr_pix_data1[1] = ptr_pix_data2[1];
		ptr_pix_data1[2] = ptr_pix_data2[2];
		ptr_pix_data1[3] = ptr_pix_data2[3];
	}
	else
	{
		ptr_pix_data1[0] = ptr_pix_data2[3];
		ptr_pix_data1[1] = ptr_pix_data2[2];
		ptr_pix_data1[2] = ptr_pix_data2[1];
		ptr_pix_data1[3] = ptr_pix_data2[0];
	}
}

double	calculate_angle(int orientation, int n_collumn)
{
	double	angle;

	angle = ((double)(orientation + ((double)FOV / (double)2))
			- (double)((double)n_collumn
				* ((double)FOV / (double)SCREEN_WIDTH)));
	if (angle < (double)0)
		angle = (double)360 + angle;
	else if (angle > (double)359)
		angle = angle - (double)359;
	return (angle);
}
