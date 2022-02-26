/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:24:37 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/26 18:32:59 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdbool.h>

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef	struct s_conf
{
	char			*N;
	char			*S;
	char			*O;
	char			*E;
	struct s_rgb	C;
	struct s_rgb	F;
	char			**map;
}	t_conf;

char	*get_next_line(int fd);

bool	is_valid_file_name(char *file_name);

void	print_error(char *error);

int		str_len(char *str);
bool	is_same_string(char *str1, char *str2);

#endif