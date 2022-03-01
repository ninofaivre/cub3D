/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:47:19 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/01 13:05:27 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

char	*open_texture(char *str, int i)
{
	int	fd;

	fd = open(&str[i], O_RDONLY);
	if (fd == -1)
	{
		print_error("Wrong texture's PATH/NAME \n");
		return (NULL);
	}
	close(fd);
	return (str_dupe(&str[i]));
}

bool	put_texture_in_struct(char *str, int i, char **ptr_path_texture)
{
	i += 1 + !(str[i] == 'S' && str[i + 1] != 'O');
	i = skip_space(str, i);
	if (*ptr_path_texture)
	{
		print_error("double texture\n");
		return (false);
	}
	*ptr_fd_texture = open_texture(str, i);
	if (!*ptr_fd_texture)
		return (false);
	return (true);
}

bool	pars_texture_info(char *str, int i, t_conf *conf)
{
	if (str[i] == 'N' && str[i + 1] == 'O')
		return (put_texture_in_struct(str, i, &conf->NO));
	else if (str[i] == 'S' && str[i + 1] == 'O')
		return (put_texture_in_struct(str, i, &conf->SO));
	else if (str[i] == 'W' && str[i + 1] == 'E')
		return (put_texture_in_struct(str, i, &conf->WE));
	else if (str[i] == 'E' && str[i + 1] == 'A')
		return (put_texture_in_struct(str, i, &conf->EA));
	else if (str[i] == 'S' && str[i + 1] == ' ')
		return (put_texture_in_struct(str, i, &conf->S));
	else
		return (false);
	return (true);
}
