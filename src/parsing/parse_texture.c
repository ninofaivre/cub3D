/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:47:19 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 19:11:52 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static char	*open_texture(char *str, int i)
{
	int		fd;
	char	*path_texture;

	fd = open(&str[i], O_RDONLY);
	if (fd == -1)
	{
		print_error("Wrong texture's RIGHT/PATH/NAME\n");
		return (NULL);
	}
	close(fd);
	path_texture = str_dupe(&str[i]);
	if (!path_texture)
		print_error("A malloc failed\n");
	return (path_texture);
}

static bool	put_texture_in_struct(char *str, int i, char **ptr_path_texture)
{
	i += 2;
	i = skip_space(str, i);
	if (*ptr_path_texture)
	{
		print_error("double texture\n");
		return (false);
	}
	*ptr_path_texture = open_texture(str, i);
	if (!*ptr_path_texture)
		return (false);
	return (true);
}

bool	pars_texture_info(char *str, int i, t_conf *conf)
{
	if (str[i] == 'N' && str[i + 1] == 'O')
		return (put_texture_in_struct(str, i, &conf->texture_path[north]));
	else if (str[i] == 'S' && str[i + 1] == 'O')
		return (put_texture_in_struct(str, i, &conf->texture_path[south]));
	else if (str[i] == 'W' && str[i + 1] == 'E')
		return (put_texture_in_struct(str, i, &conf->texture_path[west]));
	else if (str[i] == 'E' && str[i + 1] == 'A')
		return (put_texture_in_struct(str, i, &conf->texture_path[east]));
	else
	{
		print_error("Wrong info\n");
		return (false);
	}
	return (true);
}
