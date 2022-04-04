/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:42:12 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 18:36:53 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <stdlib.h>

static bool	pars_string_info(char *str, t_conf *conf)
{
	int	i;

	i = 0;
	i = skip_space(str, i);
	if (is_charset(str[i], "NSWE"))
		return (pars_texture_info(str, i, conf));
	else if (str[i] == 'F')
		return (pars_rgb(str, i, &conf->floor_rgb));
	else if (str[i] == 'C')
		return (pars_rgb(str, i, &conf->ceilling_rgb));
	else
	{
		print_error("Wrong info\n");
		return (false);
	}
}

static bool	is_info_full(t_conf *conf)
{
	if (!conf->texture_path[north])
		return (false);
	else if (!conf->texture_path[south])
		return (false);
	else if (!conf->texture_path[east])
		return (false);
	else if (!conf->texture_path[west])
		return (false);
	else if (!conf->ceilling_rgb)
		return (false);
	else if (!conf->floor_rgb)
		return (false);
	return (true);
}

bool	parsing_file(int fd_conf, t_conf *conf)
{
	char	*str;

	str = get_next_line(fd_conf);
	while (str)
	{
		if (str[str_len(str) - 1] == '\n')
			str[str_len(str) - 1] = '\0';
		if (str_len(str) && !pars_string_info(str, conf))
		{
			free(str);
			return (false);
		}
		if (is_info_full(conf))
		{
			free(str);
			return (true);
		}
		free(str);
		str = get_next_line(fd_conf);
	}
	return (false);
}
