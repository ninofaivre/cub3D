/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:35:27 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/04 21:34:44 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>

static void	free_texture_path(char **texture_path)
{
	if (!texture_path)
		return ;
	if (texture_path[north])
		free(texture_path[north]);
	if (texture_path[south])
		free(texture_path[south]);
	if (texture_path[west])
		free(texture_path[west]);
	if (texture_path[east])
		free(texture_path[east]);
	free(texture_path);
}

static void	free_conf(t_conf *conf)
{
	if (!conf)
		return ;
	if (conf->texture_path)
		free_texture_path(conf->texture_path);
	if (conf->ceilling_rgb)
		free(conf->ceilling_rgb);
	if (conf->floor_rgb)
		free(conf->floor_rgb);
	free(conf);
}

static void	free_map(t_map *map)
{
	if (map && map->content)
		free_str_tab(&(map->content));
	if (map)
		free(map);
}

void	free_info(t_global_info *info)
{
	if (!info)
		return ;
	if (info->map)
		free_map(info->map);
	if (info->conf)
		free_conf(info->conf);
	free(info);
}

void	print_error(char *error)
{
	write(2, "Error\n", 6);
	write(2, error, str_len(error));
}
