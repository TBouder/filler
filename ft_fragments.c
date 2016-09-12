/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fragments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbouder <tbouder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 15:18:28 by tbouder           #+#    #+#             */
/*   Updated: 2016/09/12 15:21:40 by tbouder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		ft_malloc_fragments_piece(t_env *env)
{
	int		i;

	i = 0;
	env->fragments = (int **)malloc(sizeof(int *) * env->nb_fragments);
	while (i < env->nb_fragments)
	{
		env->fragments[i] = (int *)malloc(sizeof(int) * 2);
		i++;
	}
}

void			ft_extract_fragments_piece(t_env *env)
{
	int		x;
	int		y;
	int		i;

	i = 0;
	y = 0;
	ft_malloc_fragments_piece(env);
	while (y < MAX_PIECE_Y)
	{
		x = 0;
		while (x < MAX_PIECE_X)
		{
			if (PIECE(y, x) == '*')
			{
				env->fragments[i][0] = y;
				env->fragments[i][1] = x;
				i++;
			}
			x++;
		}
		y++;
	}
}

int				ft_test_fragments(t_env *env, int pos_x, int pos_y)
{
	int		i;
	int		x;
	int		y;
	int		star_match;

	i = 0;
	star_match = 0;
	while (i < env->nb_fragments)
	{
		x = env->fragments[i][1] + pos_x;
		y = env->fragments[i][0] + pos_y;
		if (y > MAX_MAP_Y - 1 || x > MAX_MAP_X - 1)
			return (0);
		if (MAP(y, x) == env->letter_player)
			star_match++;
		if (MAP(y, x) == env->letter_adv || star_match > 1)
			return (0);
		i++;
	}
	if (star_match == 1)
		return (1);
	return (0);
}
