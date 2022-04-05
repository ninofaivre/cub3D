/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:54:40 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/05 19:33:00 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include "mlx.h"
#include <stdlib.h>

void	raycast_clean(t_global_info *info)
{
	mlx_destroy_image(info->mlx, info->frame->img);
	mlx_destroy_image(info->mlx, info->texture->north.img);
	mlx_destroy_image(info->mlx, info->texture->west.img);
	mlx_destroy_image(info->mlx, info->texture->east.img);
	mlx_destroy_image(info->mlx, info->texture->south.img);
	free(info->column_info);
	mlx_destroy_window(info->mlx, info->win);
	mlx_destroy_display(info->mlx);
	free(info->mlx);
	free_info(info);
}
