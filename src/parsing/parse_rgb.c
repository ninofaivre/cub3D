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
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] != ',' && str[i])
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

static bool	error_rgb(int error)
{
	if (error > 0)
	{
		print_error("Too much F or C\n");
		return (false);
	}
	if (error == -1)
	{
		print_error("Alloc\n");
		return (false);
	}
	return (true);
}

static bool	check_fake_atoi(int color_value)
{
	if (color_value == -1)
		print_error("Wrong char in color value\n");
	else if (color_value > 255)
		print_error("Color value too high\n");
	return (color_value >= 0 && color_value <= 255);
}

bool	pars_rgb(char *str, int i, char **rgb)
{
	if (*rgb != NULL)
		return (error_rgb(1));
	*rgb = malloc(sizeof(char) * 4);
	if (!*rgb)
		return (error_rgb(-1));
	(*rgb)[0] = 0;
	i = skip_space(str, ++i);
	if (!check_fake_atoi(fake_atoi(str, i)))
		return (false);
	(*rgb)[1] = fake_atoi(str, i);
	i = next_nb(str, i);
	if (!check_fake_atoi(fake_atoi(str, i)))
		return (false);
	(*rgb)[2] = fake_atoi(str, i);
	i = next_nb(str, i);
	if (!check_fake_atoi(fake_atoi(str, i)))
		return (false);
	(*rgb)[3] = fake_atoi(str, i);
	i = next_nb(str, i);
	if (str[i] || str[i - 1] == ',')
	{
		print_error("Char after last number\n");
		return (false);
	}
	return (true);
}
