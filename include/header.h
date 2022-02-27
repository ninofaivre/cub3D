/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:24:37 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/27 18:50:51 by paboutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

#include <stdbool.h>

typedef struct s_position
{
	float	x;
	float	y;
}	t_position;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_player
{
	struct s_position	position;
	float				orientation;
}	t_player;

typedef struct s_map
{
	char	**content;
	int		width;
	int		height;
}	t_map;

typedef	struct s_conf
{
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	char			*S;
	struct s_rgb	C;
	struct s_rgb	F;
}	t_conf;

char	*get_next_line(int fd);

bool	is_valid_file_name(char *file_name);

void	print_error(char *error);

int		str_len(char *str);
bool	is_same_string(char *str1, char *str2);
bool	is_charset(char c, char *charset);

char	**str_tab_dupe(char **str_tab);
char	**add_str_to_str_tab(char **str_tab, char *str);
int		str_tab_len(char **str_tab);
char	**free_str_tab(char ***str_tab);
void	print_str_tab(char **str_tab);

bool	parse_map(struct s_map *map, struct s_player *player);

#endif