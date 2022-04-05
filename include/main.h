/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:49:33 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/05 21:45:25 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdbool.h>

typedef struct s_key
{
	bool	z;
	bool	q;
	bool	s;
	bool	d;
	bool	l_arrow;
	bool	r_arrow;
	void	*mlx;
}	t_key;

void	key_hook_press(int keycode, t_key *key);
void	key_hook_release(int keycode, t_key *key);

#endif
