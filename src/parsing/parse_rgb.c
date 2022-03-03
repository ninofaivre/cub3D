/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:47:19 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/03 17:55:09 by nfaivre          ###   ########.fr       */
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
	if (error == -1)
	{
		print_error("Alloc\n");
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

bool	pars_rgb(char *str, int i, t_rgb **rgb)
{
	if (*rgb)
		return (error_rgb(1, 0, 0, 0));
	printf("on est dans pars_rgb \n");
	*rgb = malloc(sizeof(t_rgb));
	if (!*rgb)
		return (error_rgb(-1, 0, 0, 0));
	i = skip_space(str, ++i);
	(*rgb)->r = fake_atoi(str, i);
	i = next_nb(str, i);
	(*rgb)->g = fake_atoi(str, i);
	i = next_nb(str, i);
	(*rgb)->b = fake_atoi(str, i);
	return (error_rgb(0, (*rgb)->r, (*rgb)->g, (*rgb)->b));
}
