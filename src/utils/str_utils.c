/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:56:33 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/05 21:20:45 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

char	*str_dupe(char *str)
{
	int		i;
	char	*duped;

	i = 0;
	duped = malloc(sizeof(char) * (str_len(str) + 1));
	if (!duped)
		return (NULL);
	while (str[i])
	{
		duped[i] = str[i];
		i++;
	}
	duped[i] = '\0';
	return (duped);
}

void	str_ncpy(char *dest, char *src, int n_char)
{
	if (!src || !dest || n_char <= 0)
		return ;
	while (n_char--)
		dest[n_char] = src[n_char];
}
