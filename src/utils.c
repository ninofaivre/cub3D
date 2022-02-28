/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:27:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/28 23:58:48 by paboutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

int	str_len(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

bool	is_same_string(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (false);
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 == *str2);
}

bool	is_charset(char c, char *charset)
{
	if (!charset)
		return (false);
	while (*charset)
	{
		if (*charset == c)
			return (true);
		charset++;
	}
	return (false);
}

int	skip_space(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}