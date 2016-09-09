/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/29 17:19:43 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/09 20:08:35 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char		**ft_dbmalloc(int x, int y)
{
	char	**str;
	int		i;

	i = 0;
	str = (char **)malloc(sizeof(char *) * y + 1);
	while (i <= y)
	{
		str[i] = ft_strnew(x);
		i++;
	}
	return (str);
}

/*
** The ft_isletter() function will check if the pos XY is empty or not and
** will return -1 if there is an error, 0 if the pos is empty ('.'), 1 if there
** is the same letter than the player letter, and 2 in the other case.
*/
int			ft_isletter(t_env *env, int x, int y)
{
	if (x > env->map_size_x || y > env->map_size_y)
		return (-1);
	if (env->letter_player == 'O')
	{
		if (env->map[y][x] == 'o' || env->map[y][x] == 'O')
			return (1);
		else if (env->map[y][x] == 'x' || env->map[y][x] == 'X')
			return (2);
	}
	else if (env->letter_player == 'X')
	{
		if (env->map[y][x] == 'x' || env->map[y][x] == 'X')
			return (1);
		else if (env->map[y][x] == 'o' || env->map[y][x] == 'O')
			return (2);
	}
	return (0);
}

/*
** The ft_detail_piece() functil will count the number of '*' in the piece and
** return it
*/
int			ft_detail_piece(t_env *env)
{
	int		x;
	int		y;
	int		nb;

	y = 0;
	nb = 0;
	while (y < env->piece_size_y)
	{
		x = 0;
		while (x < env->piece_size_x)
		{
			if (env->piece[y][x] == '*')
				nb++;
			x++;
		}
		y++;
	}
	return (nb);
}
