/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nino <nino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 10:51:37 by nino              #+#    #+#             */
/*   Updated: 2021/09/01 12:05:07 by nino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(int i)
{
	void			*toalloc;
	unsigned char	*ptr_toalloc;

	if (i <= 0)
		return ((void *) NULL);
	toalloc = (void *)(malloc(i));
	if (!toalloc)
		return (NULL);
	ptr_toalloc = (unsigned char *)toalloc;
	while (i--)
		*ptr_toalloc++ = '\0';
	return (toalloc);
}

void	ft_strcpymod(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str2[i] != '\0')
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_search(char	*str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != c)
		return (-1);
	return (i);
}

char	*ft_strjoinmod(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*cpy;

	i = 0;
	j = 0;
	cpy = (char *)ft_calloc(ft_strlen (str1) + ft_strlen (str2) + 1);
	if (!cpy)
		return ((char *) NULL);
	if (str1)
		while (str1[j] != '\0')
			cpy[i++] = str1[j++];
	j = 0;
	while (str2[j] != '\0')
		cpy[i++] = str2[j++];
	cpy[i] = '\0';
	if (str1)
		free (str1);
	return (cpy);
}
