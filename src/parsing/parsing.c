/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:16:42 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 19:12:16 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static bool	is_valid_file_name(char *file_name)
{
	return (str_len(file_name) > 4
		&& is_same_string(&file_name[str_len(file_name) - 4], ".cub"));
}

static bool	check_argc_and_file_name(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error("n_arg\n");
		return (true);
	}
	if (is_valid_file_name(argv[1]) == false)
	{
		print_error("extension\n");
		return (true);
	}
	return (false);
}

static t_global_info	*error_parsing(t_global_info *info,
int fd_conf, char *error)
{
	get_next_line(-1);
	if (fd_conf > 0)
		close(fd_conf);
	if (info)
		free_info(info);
	if (error)
		print_error(error);
	return (NULL);
}

static bool	init_info(t_global_info *info)
{
	info->map = NULL;
	info->conf = malloc(sizeof(t_conf));
	if (!info->conf)
		return (true);
	info->conf->ceilling_rgb = NULL;
	info->conf->floor_rgb = NULL;
	info->conf->texture_path = malloc(sizeof(char *) * 4);
	if (!info->conf->texture_path)
		return (true);
	info->conf->texture_path[north] = NULL;
	info->conf->texture_path[south] = NULL;
	info->conf->texture_path[west] = NULL;
	info->conf->texture_path[east] = NULL;
	return (false);
}

t_global_info	*parsing(int argc, char **argv)
{
	int				fd_conf;
	t_global_info	*info;

	if (check_argc_and_file_name(argc, argv))
		exit (EXIT_FAILURE);
	fd_conf = open(argv[1], O_RDONLY);
	if (fd_conf == -1)
		return (error_parsing(NULL, fd_conf, "FILE\n"));
	info = malloc(sizeof(t_global_info));
	if (!info || init_info(info))
		return (error_parsing(info, fd_conf, "Alloc\n"));
	if (!parsing_file(fd_conf, info->conf))
		return (error_parsing(info, fd_conf, NULL));
	info->map = get_map(fd_conf);
	if (!info->map)
		return (error_parsing(info, fd_conf, "Alloc\n"));
	if (parse_map(info->map, &(info->player)))
		return (error_parsing(info, fd_conf, NULL));
	close(fd_conf);
	return (info);
}
