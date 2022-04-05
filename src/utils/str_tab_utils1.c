/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tab_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:42:00 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/05 21:20:28 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

char	**free_str_tab(char ***str_tab)
{
	int	i;

	i = 0;
	if (!*str_tab)
		return (NULL);
	while ((*str_tab)[i])
	{
		free((*str_tab)[i]);
		(*str_tab)[i] = NULL;
		i++;
	}
	free(*str_tab);
	*str_tab = NULL;
	return (NULL);
}

int	str_tab_len(char **str_tab)
{
	int	i;

	i = 0;
	if (!str_tab)
		return (0);
	while (str_tab[i])
		i++;
	return (i);
}

char	**add_str_to_str_tab(char **str_tab, char *str)
{
	int		i;
	char	**new_str_tab;

	i = 0;
	new_str_tab = malloc(sizeof(char *) * (str_tab_len(str_tab) + 2));
	if (!new_str_tab)
	{
		if (str_tab)
			free(str_tab);
		return (NULL);
	}
	while (str_tab && str_tab[i])
	{
		new_str_tab[i] = str_tab[i];
		i++;
	}
	new_str_tab[i] = str;
	new_str_tab[i + 1] = NULL;
	if (str_tab)
		free(str_tab);
	return (new_str_tab);
}

char	**str_tab_dupe(char **str_tab)
{
	int		i;
	char	**duped;

	i = 0;
	if (!str_tab)
		return (NULL);
	duped = malloc(sizeof(char *) * (str_tab_len(str_tab) + 1));
	if (!duped)
		return (NULL);
	while (*str_tab)
	{
		duped[i++] = str_dupe(*str_tab);
		if (!duped[i - 1])
			return (free_str_tab(&duped));
		str_tab++;
	}
	duped[i] = NULL;
	return (duped);
}
