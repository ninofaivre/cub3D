/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:42:12 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/26 18:11:21 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
char	put_string_struc(char *str, int i)
{
	int	j;
	char	*new_str;
	
	j = 0;
	while (str[i + j] !+ '\0')
		j++;
	new_str = malloc(sizeof(char) * j + 1);
	if (!new_str)
		return (NULL);
	new_str[j + 1] = '\0';
	while (j)
	{
		new_str[j] = str[i + j];
		j--;
	}
	return (new_str);
}

bool	pars_texture_info(char *str, int i, t_conf *conf)
{
	if ((str[i] == 'N' && str[i + 1] == 'O')
	{
		i = skip_space(str, ++i);
		conf->NO = put_string_struct(str, i);
	}
	else if (str[i] == 'S' && str[i + 1] == 'O')
	{
		i = skip_space(str, ++i);
		conf->SO = put_string_struct(str, i);
	}
	else if (str[i] == 'W' && str[i + 1] == 'E')
	{
		i = skip_space(str, ++i);
		conf->WE = put_string_struct(str, i);
	}
	else if (str[i] == 'E' && str[i + 1] == 'A')
	{
		i = skip_space(str, ++i);
		conf->EA = put_string_struct(str, i);
	}
	else if (str[i] == 'S' && str[i + 1] == ' ')
	{
		i = skip_space(str, i++);
		conf->S = put_string_struct(str, i);
	}
	else
		return (false);
	return (true);
}
int	fake_atoi(char *str, int i)
{
	int	nb;

	nb = 0;
	while(str[i] != ',')
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

bool	pars_RGB(char *str, int i, t_conf *conf)
{
	if (str[i] == 'F')
	{
		i = skip_space(str, ++i);
		conf->F->R = fake_atoi(str, i);
		i = next_nb(str, i);
		conf->F->G = fake_atoi(str, i);
		i = next_nb(str, i);
		conf->F->B = fake_atoi(str, i);
		if (conf->F->R < 0 || conf->F->R > 255 || conf->F->G < 0 || conf->F->G > 255 || conf->F->B < 0 || conf->F->B > 255)
			return (false);
		else
			return (true);
	}
	if (str[i] == 'C')
	{
		i = skip_space(str, ++i);
		conf->C->R = fake_atoi(str, i);
		i = next_nb(str, i);
		conf->C->G = fake_atoi(str, i);
		i = next_nb(str, i);
		conf->C->B = fake_atoi(str, i);
		if (conf->C->R < 0 || conf->C->R > 255 || conf->C->G < 0 || conf->C->G > 255 || conf->C->B < 0 || conf->C->B > 255)
			return (false);
		else
			return (true);
	}
}

bool	pars_string_info(char *str, t_conf *conf)
{
	int	i;

	i = 0;
	i = skip_space(str, i);
	if (str[i] == 'N'|| str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
		return (pars_texture_info(str, i, conf));
	else if (str[i] == 'F' || str[i] == 'C')
		return (pars_RGB(str, i, conf));
	else if (str[i] == '\n' || str[i] == '\0')
		return (true);
	else if (str[i] == '1')
	{
		add_str_to_str_tab(conf->map, str);
		return (true);
	}
	else
		return (false);
}


bool	parsing_file(int fd_conf, t_conf *conf)
{
	char	*str;

	str = get_next_line(fd_conf);
	while (str)
	{
		if (!pars_string_info(str, conf)
			return (false);
		str = get_next_line(fd_conf);
	}
	return (true);
}