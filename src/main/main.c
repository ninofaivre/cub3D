/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:25:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/05 21:17:36 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "calculation.h"
#include "parsing.h"
#include "mlx.h"
#include <stdlib.h>

static void	start_raycast(t_global_info *info)
{
	t_put_texture	put_texture;
	t_texture		texture;
	t_img			frame;
	t_key			key;

	info->key = &key;
	info->texture = &texture;
	info->frame = &frame;
	info->put_texture = &put_texture;
	if (init_raycast_info(info))
	{
		print_error("Mlx function failed in function init_raycast_info\n");
		raycast_clean(info, true);
	}
	if (init_texture(&texture, info))
		raycast_clean(info, true);
	info->column_info = init_column_info();
	if (!info->column_info)
		raycast_clean(info, true);
	mlx_hook(info->win, 02, 1L, key_hook_press, info->key);
	mlx_hook(info->win, 03, 1L << 1, key_hook_release, info->key);
	mlx_hook(info->win, 17, 1L << 17, (void *)mlx_loop_end, (void *)info->mlx);
	mlx_loop_hook(info->mlx, display_one_frame, info);
	mlx_loop(info->mlx);
	raycast_clean(info, false);
}

int	main(int argc, char **argv)
{
	t_global_info	*info;

	info = parsing(argc, argv);
	if (!info)
		exit(EXIT_FAILURE);
	start_raycast(info);
	exit(EXIT_SUCCESS);
}
