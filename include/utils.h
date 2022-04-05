/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:38:02 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/05 21:21:20 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdbool.h>

char	*str_dupe(char *str);
void	str_ncpy(char *dest, char *src, int n_char);
int		str_len(char *str);
bool	is_same_string(char *str1, char *str2);
bool	is_charset(char c, char *charset);
int		skip_space(char *str, int i);
char	**str_tab_dupe(char **str_tab);
char	**add_str_to_str_tab(char **str_tab, char *str);
int		str_tab_len(char **str_tab);
char	**free_str_tab(char ***str_tab);
void	replace_all_charset_by_char_in_str_tab(char *charset,
			char replace, char **str_tab);
int		get_n_char_in_str_tab(char c, char **str_tab);
bool	does_str_tab_contains_empty_str(char **str_tab);
int		skip_space(char *str, int i);

#endif
