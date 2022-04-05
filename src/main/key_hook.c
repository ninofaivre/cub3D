/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:30:17 by nfaivre           #+#    #+#             */
/*   Updated: 2022/04/05 21:45:20 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "mlx.h"

#ifndef QWERTY
# define QWERTY 0
#endif

#define KEY_RIGHT_ARROW 65363
#define KEY_LEFT_ARROW 65361
#define KEY_ESCAPE 65307

void	key_hook_press(int keycode, t_key *key)
{
	if (keycode == KEY_ESCAPE)
		mlx_loop_end(key->mlx);
	else if ((keycode == 'z' && !QWERTY) || (keycode == 'w' && QWERTY))
		key->z = true;
	else if ((keycode == 'q' && !QWERTY) || (keycode == 'a' && QWERTY))
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
	if ((keycode == 'z' && !QWERTY) || (keycode == 'w' && QWERTY))
		key->z = false;
	else if ((keycode == 'q' && !QWERTY) || (keycode == 'a' && QWERTY))
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
