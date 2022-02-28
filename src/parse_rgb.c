/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:47:19 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/01 00:29:35 by paboutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int	fake_atoi(char *str, int i)
{
	int	nb;

	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

int	next_nb(char *str, int i)
{
	while (str[i] != ',' && str[i])
		i++;
	if (str[i] == ',')
		i++;
	return (i);
}

bool	error_rgb(int error, int r, int g, int b)
{
	if (error > 0)
	{
		print_error("too much F or C\n");
		return (false);
	}
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		print_error("wrong rgb\n");
		return (false);
	}
	else
		return (true);
}

bool	pars_rgb(char *str, int i, t_rgb *rgb)
{
	int	error;

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
	return (error_rgb(error, rgb->r, rgb->g, rgb->b));
}
