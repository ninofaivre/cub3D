/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:42:12 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/01 12:33:48 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

bool	is_valid_file_name(char *file_name)
{
	return (str_len(file_name) > 4
		&& is_same_string(&file_name[str_len(file_name) - 4], ".cub"));
}

bool	pars_string_info(char *str, t_conf *conf)
{
	int	i;

	i = 0;
	i = skip_space(str, i);
	if (is_charset(str[i], "NSWE"))
		return (pars_texture_info(str, i, conf));
	else if (str[i] == 'F')
		return (pars_rgb(str, i, &conf->F));
	else if (str[i] == 'C')
		return (pars_rgb(str, i, &conf->C));
	else if (str[i] == '\n')
		return (true);
	else
		return (false);
}

bool	parsing_file(int fd_conf, t_conf *conf)
{
	char	*str;

	conf->C.r = -1;
	conf->C.g = -1;
	conf->C.b = -1;
	conf->F.r = -1;
	conf->F.g = -1;
	conf->F.b = -1;
	str = get_next_line(fd_conf);
	while (str)new_str
		if (!pars_string_info(str, conf))
			return (false);
		str = get_next_line(fd_conf);
	}
	return (true);
}
