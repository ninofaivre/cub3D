/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tab_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:41:34 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/02 19:13:14 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	replace_all_charset_by_char_in_str_tab(char *charset,
char replace, char **str_tab)
{
	char	*str;

	if (!str_tab)
		return ;
	while (*str_tab)
	{
		str = *str_tab;
		while (*str)
		{
			if (is_charset(*str, charset))
				*str = replace;
			str++;
		}
		str_tab++;
	}
}

int	get_n_char_in_str_tab(char c, char **str_tab)
{
	int		number;
	char	*str;

	number = 0;
	if (!str_tab)
		return (0);
	while (*str_tab)
	{
		str = *str_tab;
		while (*str)
		{
			if (*str == c)
				number++;
			str++;
		}
		str_tab++;
	}
	return (number);
}

bool	does_str_tab_contains_empty_str(char **str_tab)
{
	while (*str_tab)
	{
		if (!str_len(*str_tab))
			return (true);
		str_tab++;
	}
	return (false);
}
