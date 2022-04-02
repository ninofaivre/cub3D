/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 18:47:19 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 19:10:55 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"
#include <stdlib.h>

static int	fake_atoi(char *str, int i)
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

static int	next_nb(char *str, int i)
{
	while (str[i] != ',' && str[i])
		i++;
	if (str[i] == ',')
		i++;
	return (i);
}

static bool	error_rgb(int error, int r, int g, int b)
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
		return (false);
	else
		return (true);
}

bool	pars_rgb(char *str, int i, char **rgb)
{
	if (*rgb != NULL)
		return (error_rgb(1, 0, 0, 0));
	*rgb = malloc(sizeof(char) * 4);
	if (!*rgb)
		return (error_rgb(-1, 0, 0, 0));
	(*rgb)[0] = 0;
	i = skip_space(str, ++i);
	(*rgb)[1] = fake_atoi(str, i);
	i = next_nb(str, i);
	(*rgb)[2] = fake_atoi(str, i);
	i = next_nb(str, i);
	(*rgb)[3] = fake_atoi(str, i);
	return (error_rgb(0, (unsigned char)(*rgb)[1], (unsigned char)(*rgb)[2],
			(unsigned char)(*rgb)[3]));
}
