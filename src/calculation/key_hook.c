/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/28 20:35:35 by paboutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.h>
#include <calculation.h>

void	key_hook_press(int keycode, t_key *key)
{
	if (keycode == 'z')
		key->z = true;
	else if (keycode == 'q')
		key->q = true;
	else if (keycode == 's')
		key->s = true;
	else if (keycode == 'd')
		key->d = true;
	else if (keycode == KEY_LEFT_ARROW)
		key->l_arrow = true;
	else if (keycode == KEY_RIGHT_ARROW)
		key->r_arrow = true;
}

void	key_hook_release(int keycode, t_key *key)
{
	if (keycode == 'z')
		key->z = false;
	else if (keycode == 'q')
		key->q = false;
	else if (keycode == 's')
		key->s = false;
	else if (keycode == 'd')
		key->d = false;
	else if (keycode == KEY_LEFT_ARROW)
		key->l_arrow = false;
	else if (keycode == KEY_RIGHT_ARROW)
		key->r_arrow = false;
}
