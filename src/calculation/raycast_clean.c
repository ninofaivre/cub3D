/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:54:40 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/05 19:56:16 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calculation.h"
#include "mlx.h"
#include <stdlib.h>

void	raycast_clean(t_global_info *info, bool error)
{
	if (info->frame->img)
		mlx_destroy_image(info->mlx, info->frame->img);
	if (info->texture->north.img)
		mlx_destroy_image(info->mlx, info->texture->north.img);
	if (info->texture->west.img)
		mlx_destroy_image(info->mlx, info->texture->west.img);
	if (info->texture->east.img)
		mlx_destroy_image(info->mlx, info->texture->east.img);
	if (info->texture->south.img)
		mlx_destroy_image(info->mlx, info->texture->south.img);
	if (info->column_info)
		free(info->column_info);
	if (info->win)
		mlx_destroy_window(info->mlx, info->win);
	if (info->mlx)
		mlx_destroy_display(info->mlx);
	if (info->mlx)
		free(info->mlx);
	free_info(info);
	if (error)
		exit(EXIT_FAILURE);
}
