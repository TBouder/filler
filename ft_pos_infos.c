/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pos_infos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 10:50:19 by tbouder           #+#    #+#             */
/*   Updated: 2016/08/13 10:57:49 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** The ft_hori_verti() function will check the orientation of the piece and
** return 1 if it is Horizontal, -1 if Vertical or 0 if it's a square.
*/
int			ft_hori_verti(t_env *env)
{
	if (env->piece_size_x > env->piece_size_y)
		return (1); //Horizontal
	else if (env->piece_size_x < env->piece_size_y)
		return (-1); //Vertical
	else
		return (0); //Square
}

/*
** The ft_pos_cmp_middle_y() function will check the Y position of the piece
** according to the middle and return -1 if Y is bellow than the middle and
** 1 on the other cases.
*/
int			ft_pos_cmp_middle_y(t_env *env, int y)
{
	// 1 => top
	// -1 => down
	if (y > env->middle_y1)
		return (-1);
	else if (y < env->middle_y2 && env->middle_y2 != -1)
		return (1);
	else
		return (1);
}

/*
** The ft_pos_cmp_middle_x() function will check the X position of the piece
** according to the middle and return -1 if Y is righter than the middle and
** 1 on the other cases.
*/
int			ft_pos_cmp_middle_x(t_env *env, int x)
{
	// 1 => right
	// -1 => left
	if (x > env->middle_x1)
		return (-1);
	else if (x < env->middle_x2 && env->middle_x2 != -1)
		return (1);
	else
		return (1);
}
