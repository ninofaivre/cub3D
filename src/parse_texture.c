/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:47:19 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/01 00:27:12 by paboutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

char	*split_path_texture(char *str, int i)
{
	int		j;
	char	*new_str;

	j = str_len(&str[i]);
	new_str = malloc(sizeof(char) * (j + 1));
	j--;
	if (!new_str)
		return (NULL);
	str_ncpy(new_str, &str[i], j);
	j = open(new_str, O_RDONLY);
	if (j == -1)
	{
		print_error("Wrong texture's PATH/NAME \n");
		close (j);
		return (NULL);
	}
	close (j);
	return (new_str);
}

bool	put_texture_in_struct(char *str, int i, char **texture)
{
	i += 2;
	i = skip_space(str, i);
	*texture = split_path_texture(str, i);
	if (!str)
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
