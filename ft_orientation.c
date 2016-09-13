/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_orientation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 15:22:28 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/13 10:04:50 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			ft_hori_verti(t_env *env)
{
	if (MAX_PIECE_X > MAX_PIECE_Y)
		env->piece_orientation = 1;
	else if (MAX_PIECE_X < MAX_PIECE_Y)
		env->piece_orientation = -1;
	else
		env->piece_orientation = 0;
}

static int		ft_chr(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

static void		ft_choose_asign(int *x_user, int *y_user, int x, int y)
{
	*x_user = x;
	*y_user = y;
}

void			ft_choose_direction(t_env *env)
{
	int		x;
	int		x_player;
	int		y_player;
	int		x_adv;
	int		y_adv;

	env->tmp = 0;
	x_player = 0;
	x_adv = 0;
	while (env->tmp < MAX_MAP_Y)
	{
		if (!x_player && (x = ft_chr(env->map[env->tmp], env->letter_player)))
			ft_choose_asign(&x_player, &y_player, x, env->tmp);
		if (!x_adv && (x = ft_chr(env->map[env->tmp], env->letter_adv)))
			ft_choose_asign(&x_adv, &y_adv, x, env->tmp);
		if (x_adv && x_player)
			break ;
		env->tmp++;
	}
	env->direction_x = x_adv > x_player ? -1 : 1;
	env->direction_y = y_adv > y_player ? 1 : -1;
}
