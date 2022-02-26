/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:24:37 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/26 18:12:27 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdbool.h>

char	*get_next_line(int fd);

bool	is_valid_file_name(char *file_name);

void	print_error(char *error);

int		str_len(char *str);
bool	is_same_string(char *str1, char *str2);

#endif