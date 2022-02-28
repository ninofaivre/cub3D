/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:42:12 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/28 14:40:44 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

bool	is_valid_file_name(char *file_name)
{
	if (str_len(file_name) < 5)
		return (false);
	while (file_name[4])
		file_name++;
	return (is_same_string(file_name, ".cub"));
}

int		skip_space(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}
char	*put_string_struct(char *str, int i)
{
	int	j;
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
	close(j); 
	return (new_str);
}

bool	pars_texture_info(char *str, int i, t_conf *conf)
{
	if (str[i] == 'N' && str[i + 1] == 'O')
	{
		i += 2;
		i = skip_space(str, i);
		conf->NO = put_string_struct(str, i);
		if (!conf->NO)
			return (false);
	}
	else if (str[i] == 'S' && str[i + 1] == 'O')
	{
		i += 2;
		i = skip_space(str, i);
		conf->SO = put_string_struct(str, i);
		if (!conf->SO)
			return (false);
	}
	else if (str[i] == 'W' && str[i + 1] == 'E')
	{
		i += 2;
		i = skip_space(str, i);
		conf->WE = put_string_struct(str, i);
		if (!conf->WE)
			return (false);
	}
	else if (str[i] == 'E' && str[i + 1] == 'A')
	{
		i += 2;
		i = skip_space(str, i);
		conf->EA = put_string_struct(str, i);
		if (!conf->EA)
			return (false);
	}
	else if (str[i] == 'S' && str[i + 1] == ' ')
	{
		i++;
		i = skip_space(str, i);
		conf->S = put_string_struct(str, i);
		if (!conf->S)
			return (false);
	}
	else
		return (false);
	return (true);
}

int	fake_atoi(char *str, int i)
{
	int	nb;

	nb = 0;
	while(str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}
int		next_nb(char *str, int i)
{
	while (str[i] != ',' && str[i])
		i++;
	if (str[i] == ',')	
		i++;
	return (i);
}

bool	pars_RGB(char *str, int i, t_rgb *rgb)
{
	int error;

	error = 0;
	i = skip_space(str, ++i);
	if (rgb->r == -1)
		rgb->r = fake_atoi(str, i);
	else
		error++;
	i = next_nb(str, i);
	if (rgb->g == -1)
		rgb->g = fake_atoi(str, i);
	else
		error++;
	i = next_nb(str, i);
	if (rgb->b == -1)
		rgb->b = fake_atoi(str, i);
	else
		error++;
	if (error > 0)
	{
		print_error("too much F or C\n");
		return (false);
	}
	if (rgb->r < 0 || rgb->r > 255 || rgb->g < 0 || rgb->g > 255 || rgb->b < 0 || rgb->b > 255)
	{
		print_error("wrong rgb\n");
		return (false);
	}
	else
		return (true);	
}

bool	pars_string_info(char *str, t_conf *conf)
{
	int	i;

	i = 0;
	i = skip_space(str, i);
	if (is_charset(str[i], "NSWE"))
		return (pars_texture_info(str, i, conf));
	else if (str[i] == 'F')
		return (pars_RGB(str, i, &conf->F));
	else if (str[i] == 'C')
		return (pars_RGB(str, i, &conf->C));
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
	while (str)
	{
		if (!pars_string_info(str, conf))
			return (false);
		str = get_next_line(fd_conf);
	}
	return (true);
}